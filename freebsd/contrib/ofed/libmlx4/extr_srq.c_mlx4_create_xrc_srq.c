#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ buf; } ;
struct ibv_srq {int dummy; } ;
struct TYPE_10__ {struct ibv_srq srq; int /*<<< orphan*/  srq_num; } ;
struct mlx4_srq {int max_gs; int ext_srq; TYPE_3__ buf; struct mlx4_srq* wrid; scalar_t__* db; TYPE_6__ verbs_srq; scalar_t__ counter; int /*<<< orphan*/  max; int /*<<< orphan*/  lock; } ;
struct mlx4_create_xsrq {uintptr_t buf_addr; uintptr_t db_addr; int /*<<< orphan*/  ibv_cmd; } ;
struct mlx4_create_srq_resp {int /*<<< orphan*/  ibv_resp; } ;
struct TYPE_9__ {int max_wr; int max_sge; } ;
struct ibv_srq_init_attr_ex {TYPE_4__ attr; int /*<<< orphan*/  pd; } ;
struct ibv_context {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  xsrq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_DB_TYPE_RQ ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 int /*<<< orphan*/  align_queue_size (int) ; 
 struct mlx4_srq* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct mlx4_srq*) ; 
 int ibv_cmd_create_srq_ex (struct ibv_context*,TYPE_6__*,int,struct ibv_srq_init_attr_ex*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ibv_cmd_destroy_srq (struct ibv_srq*) ; 
 scalar_t__* mlx4_alloc_db (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_alloc_srq_buf (int /*<<< orphan*/ ,TYPE_4__*,struct mlx4_srq*) ; 
 int /*<<< orphan*/  mlx4_free_buf (TYPE_3__*) ; 
 int /*<<< orphan*/  mlx4_free_db (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int mlx4_store_xsrq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx4_srq*) ; 
 scalar_t__ pthread_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mctx (struct ibv_context*) ; 

struct ibv_srq *mlx4_create_xrc_srq(struct ibv_context *context,
				    struct ibv_srq_init_attr_ex *attr_ex)
{
	struct mlx4_create_xsrq cmd;
	struct mlx4_create_srq_resp resp;
	struct mlx4_srq *srq;
	int ret;

	/* Sanity check SRQ size before proceeding */
	if (attr_ex->attr.max_wr > 1 << 16 || attr_ex->attr.max_sge > 64)
		return NULL;

	srq = calloc(1, sizeof *srq);
	if (!srq)
		return NULL;

	if (pthread_spin_init(&srq->lock, PTHREAD_PROCESS_PRIVATE))
		goto err;

	srq->max     = align_queue_size(attr_ex->attr.max_wr + 1);
	srq->max_gs  = attr_ex->attr.max_sge;
	srq->counter = 0;
	srq->ext_srq = 1;

	if (mlx4_alloc_srq_buf(attr_ex->pd, &attr_ex->attr, srq))
		goto err;

	srq->db = mlx4_alloc_db(to_mctx(context), MLX4_DB_TYPE_RQ);
	if (!srq->db)
		goto err_free;

	*srq->db = 0;

	cmd.buf_addr = (uintptr_t) srq->buf.buf;
	cmd.db_addr  = (uintptr_t) srq->db;

	ret = ibv_cmd_create_srq_ex(context, &srq->verbs_srq,
				    sizeof(srq->verbs_srq),
				    attr_ex,
				    &cmd.ibv_cmd, sizeof cmd,
				    &resp.ibv_resp, sizeof resp);
	if (ret)
		goto err_db;

	ret = mlx4_store_xsrq(&to_mctx(context)->xsrq_table,
			      srq->verbs_srq.srq_num, srq);
	if (ret)
		goto err_destroy;

	return &srq->verbs_srq.srq;

err_destroy:
	ibv_cmd_destroy_srq(&srq->verbs_srq.srq);
err_db:
	mlx4_free_db(to_mctx(context), MLX4_DB_TYPE_RQ, srq->db);
err_free:
	free(srq->wrid);
	mlx4_free_buf(&srq->buf);
err:
	free(srq);
	return NULL;
}