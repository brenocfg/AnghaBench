#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ buf; } ;
struct TYPE_9__ {int wqe_cnt; scalar_t__ max_post; scalar_t__ max_gs; struct mlx4_qp* wrid; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int wqe_cnt; int wqe_shift; struct mlx4_qp* wrid; int /*<<< orphan*/  lock; } ;
struct ibv_qp {int qp_num; } ;
struct TYPE_12__ {struct ibv_qp qp; } ;
struct mlx4_qp {int sq_spare_wqes; TYPE_4__ buf; TYPE_2__ rq; TYPE_1__ sq; scalar_t__* db; TYPE_7__ verbs_qp; void* sq_signal_bits; void* doorbell_qpn; } ;
struct mlx4_create_qp {uintptr_t db_addr; uintptr_t buf_addr; int log_sq_stride; int log_sq_bb_count; int /*<<< orphan*/  ibv_cmd; int /*<<< orphan*/  reserved; scalar_t__ sq_no_prefetch; } ;
struct mlx4_context {scalar_t__ max_qp_wr; scalar_t__ max_sge; int /*<<< orphan*/  qp_table_mutex; } ;
struct TYPE_10__ {scalar_t__ max_send_wr; scalar_t__ max_recv_wr; scalar_t__ max_send_sge; scalar_t__ max_recv_sge; int max_inline_data; } ;
struct ibv_qp_init_attr_ex {int comp_mask; TYPE_3__ cap; scalar_t__ sq_sig_all; int /*<<< orphan*/  qp_type; scalar_t__ srq; } ;
struct ibv_create_qp_resp {int dummy; } ;
struct ibv_context {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_QPT_XRC_RECV ; 
 int /*<<< orphan*/  IBV_QPT_XRC_SEND ; 
 int MLX4_CREATE_QP_EX2_COMP_MASK ; 
 int MLX4_CREATE_QP_SUP_COMP_MASK ; 
 int /*<<< orphan*/  MLX4_DB_TYPE_RQ ; 
 int MLX4_WQE_CTRL_CQ_UPDATE ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 void* align_queue_size (int) ; 
 struct mlx4_qp* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct mlx4_qp*) ; 
 void* htobe32 (int) ; 
 int ibv_cmd_create_qp_ex (struct ibv_context*,TYPE_7__*,int,struct ibv_qp_init_attr_ex*,int /*<<< orphan*/ *,int,struct ibv_create_qp_resp*,int) ; 
 int /*<<< orphan*/  ibv_cmd_destroy_qp (struct ibv_qp*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__* mlx4_alloc_db (struct mlx4_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_alloc_qp_buf (struct ibv_context*,TYPE_3__*,int /*<<< orphan*/ ,struct mlx4_qp*) ; 
 int /*<<< orphan*/  mlx4_calc_sq_wqe_size (TYPE_3__*,int /*<<< orphan*/ ,struct mlx4_qp*) ; 
 int mlx4_cmd_create_qp_ex (struct ibv_context*,struct ibv_qp_init_attr_ex*,struct mlx4_create_qp*,struct mlx4_qp*) ; 
 int /*<<< orphan*/  mlx4_free_buf (TYPE_4__*) ; 
 int /*<<< orphan*/  mlx4_free_db (struct mlx4_context*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_init_qp_indices (struct mlx4_qp*) ; 
 int /*<<< orphan*/  mlx4_set_sq_sizes (struct mlx4_qp*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int mlx4_store_qp (struct mlx4_context*,int,struct mlx4_qp*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx4_context* to_mctx (struct ibv_context*) ; 

struct ibv_qp *mlx4_create_qp_ex(struct ibv_context *context,
				 struct ibv_qp_init_attr_ex *attr)
{
	struct mlx4_context *ctx = to_mctx(context);
	struct mlx4_create_qp     cmd;
	struct ibv_create_qp_resp resp;
	struct mlx4_qp		 *qp;
	int			  ret;

	/* Sanity check QP size before proceeding */
	if (ctx->max_qp_wr) { /* mlx4_query_device succeeded */
		if (attr->cap.max_send_wr  > ctx->max_qp_wr ||
		    attr->cap.max_recv_wr  > ctx->max_qp_wr ||
		    attr->cap.max_send_sge > ctx->max_sge   ||
		    attr->cap.max_recv_sge > ctx->max_sge)
			return NULL;
	} else {
		if (attr->cap.max_send_wr  > 65536 ||
		    attr->cap.max_recv_wr  > 65536 ||
		    attr->cap.max_send_sge > 64    ||
		    attr->cap.max_recv_sge > 64)
			return NULL;
	}
	if (attr->cap.max_inline_data > 1024)
		return NULL;

	if (attr->comp_mask & ~MLX4_CREATE_QP_SUP_COMP_MASK)
		return NULL;

	qp = calloc(1, sizeof *qp);
	if (!qp)
		return NULL;

	if (attr->qp_type == IBV_QPT_XRC_RECV) {
		attr->cap.max_send_wr = qp->sq.wqe_cnt = 0;
	} else {
		mlx4_calc_sq_wqe_size(&attr->cap, attr->qp_type, qp);
		/*
		 * We need to leave 2 KB + 1 WQE of headroom in the SQ to
		 * allow HW to prefetch.
		 */
		qp->sq_spare_wqes = (2048 >> qp->sq.wqe_shift) + 1;
		qp->sq.wqe_cnt = align_queue_size(attr->cap.max_send_wr + qp->sq_spare_wqes);
	}

	if (attr->srq || attr->qp_type == IBV_QPT_XRC_SEND ||
	    attr->qp_type == IBV_QPT_XRC_RECV) {
		attr->cap.max_recv_wr = qp->rq.wqe_cnt = attr->cap.max_recv_sge = 0;
	} else {
		qp->rq.wqe_cnt = align_queue_size(attr->cap.max_recv_wr);
		if (attr->cap.max_recv_sge < 1)
			attr->cap.max_recv_sge = 1;
		if (attr->cap.max_recv_wr < 1)
			attr->cap.max_recv_wr = 1;
	}

	if (mlx4_alloc_qp_buf(context, &attr->cap, attr->qp_type, qp))
		goto err;

	mlx4_init_qp_indices(qp);

	if (pthread_spin_init(&qp->sq.lock, PTHREAD_PROCESS_PRIVATE) ||
	    pthread_spin_init(&qp->rq.lock, PTHREAD_PROCESS_PRIVATE))
		goto err_free;

	if (attr->cap.max_recv_sge) {
		qp->db = mlx4_alloc_db(to_mctx(context), MLX4_DB_TYPE_RQ);
		if (!qp->db)
			goto err_free;

		*qp->db = 0;
		cmd.db_addr = (uintptr_t) qp->db;
	} else {
		cmd.db_addr = 0;
	}

	cmd.buf_addr	    = (uintptr_t) qp->buf.buf;
	cmd.log_sq_stride   = qp->sq.wqe_shift;
	for (cmd.log_sq_bb_count = 0;
	     qp->sq.wqe_cnt > 1 << cmd.log_sq_bb_count;
	     ++cmd.log_sq_bb_count)
		; /* nothing */
	cmd.sq_no_prefetch = 0;	/* OK for ABI 2: just a reserved field */
	memset(cmd.reserved, 0, sizeof cmd.reserved);
	pthread_mutex_lock(&to_mctx(context)->qp_table_mutex);

	if (attr->comp_mask & MLX4_CREATE_QP_EX2_COMP_MASK)
		ret = mlx4_cmd_create_qp_ex(context, attr, &cmd, qp);
	else
		ret = ibv_cmd_create_qp_ex(context, &qp->verbs_qp,
					   sizeof(qp->verbs_qp), attr,
					   &cmd.ibv_cmd, sizeof(cmd), &resp,
					   sizeof(resp));
	if (ret)
		goto err_rq_db;

	if (qp->sq.wqe_cnt || qp->rq.wqe_cnt) {
		ret = mlx4_store_qp(to_mctx(context), qp->verbs_qp.qp.qp_num, qp);
		if (ret)
			goto err_destroy;
	}
	pthread_mutex_unlock(&to_mctx(context)->qp_table_mutex);

	qp->rq.wqe_cnt = qp->rq.max_post = attr->cap.max_recv_wr;
	qp->rq.max_gs  = attr->cap.max_recv_sge;
	if (attr->qp_type != IBV_QPT_XRC_RECV)
		mlx4_set_sq_sizes(qp, &attr->cap, attr->qp_type);

	qp->doorbell_qpn    = htobe32(qp->verbs_qp.qp.qp_num << 8);
	if (attr->sq_sig_all)
		qp->sq_signal_bits = htobe32(MLX4_WQE_CTRL_CQ_UPDATE);
	else
		qp->sq_signal_bits = 0;

	return &qp->verbs_qp.qp;

err_destroy:
	ibv_cmd_destroy_qp(&qp->verbs_qp.qp);

err_rq_db:
	pthread_mutex_unlock(&to_mctx(context)->qp_table_mutex);
	if (attr->cap.max_recv_sge)
		mlx4_free_db(to_mctx(context), MLX4_DB_TYPE_RQ, qp->db);

err_free:
	free(qp->sq.wrid);
	if (qp->rq.wqe_cnt)
		free(qp->rq.wrid);
	mlx4_free_buf(&qp->buf);

err:
	free(qp);

	return NULL;
}