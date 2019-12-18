#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct scatterlist {int dummy; } ;
struct request_queue {struct carm_port* queuedata; } ;
struct request {int /*<<< orphan*/  tag; } ;
struct carm_request {int n_elem; int msg_bucket; struct scatterlist* sg; void* msg_type; } ;
struct carm_port {int /*<<< orphan*/  port_no; struct carm_host* host; } ;
struct carm_msg_sg {void* len; void* start; } ;
struct carm_msg_rw {int sg_count; struct carm_msg_sg* sg; void* lba_count; void* lba_high; void* lba; void* handle; int /*<<< orphan*/  sg_type; int /*<<< orphan*/  id; void* type; } ;
struct carm_host {int hw_sg_used; int /*<<< orphan*/  lock; TYPE_1__* pdev; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {struct request_queue* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_DEV_RESOURCE ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CARM_MAX_HOST_SG ; 
 int /*<<< orphan*/  CARM_MAX_REQ_SG ; 
 void* CARM_MSG_READ ; 
 void* CARM_MSG_WRITE ; 
 scalar_t__ REQ_OP_DRV_OUT ; 
 int /*<<< orphan*/  SGT_32BIT ; 
 int TAG_ENCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VPRINTK (char*,...) ; 
 scalar_t__ WRITE ; 
 struct carm_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int blk_rq_map_sg (struct request_queue*,struct request*,struct scatterlist*) ; 
 int blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 int carm_lookup_bucket (unsigned int) ; 
 int /*<<< orphan*/  carm_push_q (struct carm_host*,struct request_queue*) ; 
 scalar_t__ carm_ref_msg (struct carm_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carm_round_robin (struct carm_host*) ; 
 int /*<<< orphan*/  carm_rq_dir (struct request*) ; 
 int carm_send_msg (struct carm_host*,struct carm_request*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int dma_map_sg (int /*<<< orphan*/ *,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ req_op (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int sg_dma_address (struct scatterlist*) ; 
 int sg_dma_len (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t carm_queue_rq(struct blk_mq_hw_ctx *hctx,
				  const struct blk_mq_queue_data *bd)
{
	struct request_queue *q = hctx->queue;
	struct request *rq = bd->rq;
	struct carm_port *port = q->queuedata;
	struct carm_host *host = port->host;
	struct carm_request *crq = blk_mq_rq_to_pdu(rq);
	struct carm_msg_rw *msg;
	struct scatterlist *sg;
	int i, n_elem = 0, rc;
	unsigned int msg_size;
	u32 tmp;

	crq->n_elem = 0;
	sg_init_table(crq->sg, CARM_MAX_REQ_SG);

	blk_mq_start_request(rq);

	spin_lock_irq(&host->lock);
	if (req_op(rq) == REQ_OP_DRV_OUT)
		goto send_msg;

	/* get scatterlist from block layer */
	sg = &crq->sg[0];
	n_elem = blk_rq_map_sg(q, rq, sg);
	if (n_elem <= 0)
		goto out_ioerr;

	/* map scatterlist to PCI bus addresses */
	n_elem = dma_map_sg(&host->pdev->dev, sg, n_elem, carm_rq_dir(rq));
	if (n_elem <= 0)
		goto out_ioerr;

	/* obey global hardware limit on S/G entries */
	if (host->hw_sg_used >= CARM_MAX_HOST_SG - n_elem)
		goto out_resource;

	crq->n_elem = n_elem;
	host->hw_sg_used += n_elem;

	/*
	 * build read/write message
	 */

	VPRINTK("build msg\n");
	msg = (struct carm_msg_rw *) carm_ref_msg(host, rq->tag);

	if (rq_data_dir(rq) == WRITE) {
		msg->type = CARM_MSG_WRITE;
		crq->msg_type = CARM_MSG_WRITE;
	} else {
		msg->type = CARM_MSG_READ;
		crq->msg_type = CARM_MSG_READ;
	}

	msg->id		= port->port_no;
	msg->sg_count	= n_elem;
	msg->sg_type	= SGT_32BIT;
	msg->handle	= cpu_to_le32(TAG_ENCODE(rq->tag));
	msg->lba	= cpu_to_le32(blk_rq_pos(rq) & 0xffffffff);
	tmp		= (blk_rq_pos(rq) >> 16) >> 16;
	msg->lba_high	= cpu_to_le16( (u16) tmp );
	msg->lba_count	= cpu_to_le16(blk_rq_sectors(rq));

	msg_size = sizeof(struct carm_msg_rw) - sizeof(msg->sg);
	for (i = 0; i < n_elem; i++) {
		struct carm_msg_sg *carm_sg = &msg->sg[i];
		carm_sg->start = cpu_to_le32(sg_dma_address(&crq->sg[i]));
		carm_sg->len = cpu_to_le32(sg_dma_len(&crq->sg[i]));
		msg_size += sizeof(struct carm_msg_sg);
	}

	rc = carm_lookup_bucket(msg_size);
	BUG_ON(rc < 0);
	crq->msg_bucket = (u32) rc;
send_msg:
	/*
	 * queue read/write message to hardware
	 */
	VPRINTK("send msg, tag == %u\n", rq->tag);
	rc = carm_send_msg(host, crq, rq->tag);
	if (rc) {
		host->hw_sg_used -= n_elem;
		goto out_resource;
	}

	spin_unlock_irq(&host->lock);
	return BLK_STS_OK;
out_resource:
	dma_unmap_sg(&host->pdev->dev, &crq->sg[0], n_elem, carm_rq_dir(rq));
	carm_push_q(host, q);
	spin_unlock_irq(&host->lock);
	return BLK_STS_DEV_RESOURCE;
out_ioerr:
	carm_round_robin(host);
	spin_unlock_irq(&host->lock);
	return BLK_STS_IOERR;
}