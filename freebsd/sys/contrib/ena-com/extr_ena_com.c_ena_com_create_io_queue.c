#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ena_com_io_sq {scalar_t__ direction; size_t qid; int /*<<< orphan*/  idx; int /*<<< orphan*/  tx_max_header_size; int /*<<< orphan*/  mem_queue_type; int /*<<< orphan*/  q_depth; int /*<<< orphan*/  msix_vector; } ;
struct ena_com_io_cq {scalar_t__ direction; size_t qid; int /*<<< orphan*/  idx; int /*<<< orphan*/  tx_max_header_size; int /*<<< orphan*/  mem_queue_type; int /*<<< orphan*/  q_depth; int /*<<< orphan*/  msix_vector; } ;
struct ena_com_dev {int /*<<< orphan*/  tx_max_header_size; struct ena_com_io_sq* io_cq_queues; struct ena_com_io_sq* io_sq_queues; } ;
struct ena_com_create_io_ctx {size_t qid; scalar_t__ direction; int /*<<< orphan*/  mem_queue_type; int /*<<< orphan*/  queue_size; int /*<<< orphan*/  msix_vector; } ;

/* Variables and functions */
 int ENA_COM_INVAL ; 
 scalar_t__ ENA_COM_IO_QUEUE_DIRECTION_TX ; 
 int /*<<< orphan*/  ENA_MIN32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ENA_TOTAL_NUM_QUEUES ; 
 int /*<<< orphan*/  SZ_256 ; 
 int ena_com_create_io_cq (struct ena_com_dev*,struct ena_com_io_sq*) ; 
 int ena_com_create_io_sq (struct ena_com_dev*,struct ena_com_io_sq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_destroy_io_cq (struct ena_com_dev*,struct ena_com_io_sq*) ; 
 int ena_com_init_io_cq (struct ena_com_dev*,struct ena_com_create_io_ctx*,struct ena_com_io_sq*) ; 
 int ena_com_init_io_sq (struct ena_com_dev*,struct ena_com_create_io_ctx*,struct ena_com_io_sq*) ; 
 int /*<<< orphan*/  ena_com_io_queue_free (struct ena_com_dev*,struct ena_com_io_sq*,struct ena_com_io_sq*) ; 
 int /*<<< orphan*/  ena_trc_err (char*,size_t,size_t) ; 
 int /*<<< orphan*/  memset (struct ena_com_io_sq*,int,int) ; 

int ena_com_create_io_queue(struct ena_com_dev *ena_dev,
			    struct ena_com_create_io_ctx *ctx)
{
	struct ena_com_io_sq *io_sq;
	struct ena_com_io_cq *io_cq;
	int ret;

	if (ctx->qid >= ENA_TOTAL_NUM_QUEUES) {
		ena_trc_err("Qid (%d) is bigger than max num of queues (%d)\n",
			    ctx->qid, ENA_TOTAL_NUM_QUEUES);
		return ENA_COM_INVAL;
	}

	io_sq = &ena_dev->io_sq_queues[ctx->qid];
	io_cq = &ena_dev->io_cq_queues[ctx->qid];

	memset(io_sq, 0x0, sizeof(*io_sq));
	memset(io_cq, 0x0, sizeof(*io_cq));

	/* Init CQ */
	io_cq->q_depth = ctx->queue_size;
	io_cq->direction = ctx->direction;
	io_cq->qid = ctx->qid;

	io_cq->msix_vector = ctx->msix_vector;

	io_sq->q_depth = ctx->queue_size;
	io_sq->direction = ctx->direction;
	io_sq->qid = ctx->qid;

	io_sq->mem_queue_type = ctx->mem_queue_type;

	if (ctx->direction == ENA_COM_IO_QUEUE_DIRECTION_TX)
		/* header length is limited to 8 bits */
		io_sq->tx_max_header_size =
			ENA_MIN32(ena_dev->tx_max_header_size, SZ_256);

	ret = ena_com_init_io_sq(ena_dev, ctx, io_sq);
	if (ret)
		goto error;
	ret = ena_com_init_io_cq(ena_dev, ctx, io_cq);
	if (ret)
		goto error;

	ret = ena_com_create_io_cq(ena_dev, io_cq);
	if (ret)
		goto error;

	ret = ena_com_create_io_sq(ena_dev, io_sq, io_cq->idx);
	if (ret)
		goto destroy_io_cq;

	return 0;

destroy_io_cq:
	ena_com_destroy_io_cq(ena_dev, io_cq);
error:
	ena_com_io_queue_free(ena_dev, io_sq, io_cq);
	return ret;
}