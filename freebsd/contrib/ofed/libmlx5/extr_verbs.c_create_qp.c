#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {void* rsn; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_gs; scalar_t__ max_post; scalar_t__ wqe_cnt; int /*<<< orphan*/  wqe_shift; int /*<<< orphan*/  lock; } ;
struct TYPE_12__ {int offset; int qend; int wqe_cnt; int wqe_shift; int /*<<< orphan*/  max_post; int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {int buf; } ;
struct TYPE_11__ {int buf; } ;
struct mlx5_qp {int buf_size; int sq_buf_size; int sq_start; int atomics_enabled; scalar_t__* db; TYPE_3__ rsc; TYPE_2__ rq; TYPE_6__ sq; scalar_t__ sq_signal_bits; int /*<<< orphan*/  verbs_qp; TYPE_4__ sq_buf; TYPE_5__ buf; scalar_t__ wq_sig; struct ibv_qp* ibv_qp; } ;
struct mlx5_create_qp_resp_ex {uintptr_t buf_addr; uintptr_t sq_buf_addr; uintptr_t db_addr; int sq_wqe_count; int uidx; int /*<<< orphan*/  uuar_index; int /*<<< orphan*/  ibv_resp; int /*<<< orphan*/  ibv_cmd; int /*<<< orphan*/  rq_wqe_shift; scalar_t__ rq_wqe_count; int /*<<< orphan*/  flags; } ;
struct mlx5_create_qp_resp {uintptr_t buf_addr; uintptr_t sq_buf_addr; uintptr_t db_addr; int sq_wqe_count; int uidx; int /*<<< orphan*/  uuar_index; int /*<<< orphan*/  ibv_resp; int /*<<< orphan*/  ibv_cmd; int /*<<< orphan*/  rq_wqe_shift; scalar_t__ rq_wqe_count; int /*<<< orphan*/  flags; } ;
struct mlx5_create_qp {uintptr_t buf_addr; uintptr_t sq_buf_addr; uintptr_t db_addr; int sq_wqe_count; int uidx; int /*<<< orphan*/  uuar_index; int /*<<< orphan*/  ibv_resp; int /*<<< orphan*/  ibv_cmd; int /*<<< orphan*/  rq_wqe_shift; scalar_t__ rq_wqe_count; int /*<<< orphan*/  flags; } ;
struct mlx5_context {scalar_t__ atomic_cap; int /*<<< orphan*/  qp_table_mutex; scalar_t__ cqe_version; int /*<<< orphan*/ * dbg_fp; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_recv_sge; scalar_t__ max_recv_wr; int /*<<< orphan*/  max_send_wr; } ;
struct ibv_qp_init_attr_ex {int comp_mask; scalar_t__ qp_type; TYPE_1__ cap; scalar_t__ sq_sig_all; } ;
struct ibv_qp {void* qp_num; } ;
struct ibv_context {int dummy; } ;
typedef  int /*<<< orphan*/  resp_ex ;
typedef  int /*<<< orphan*/  resp ;
typedef  void* int32_t ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IBV_ATOMIC_HCA ; 
 scalar_t__ IBV_QPT_RAW_PACKET ; 
 int IBV_QP_INIT_ATTR_MAX_TSO_HEADER ; 
 int IBV_QP_INIT_ATTR_RX_HASH ; 
 int MLX5_CREATE_QP_EX2_COMP_MASK ; 
 int MLX5_CREATE_QP_SUP_COMP_MASK ; 
 int /*<<< orphan*/  MLX5_DBG_QP ; 
 int /*<<< orphan*/  MLX5_QP_FLAG_SCATTER_CQE ; 
 int /*<<< orphan*/  MLX5_QP_FLAG_SIGNATURE ; 
 size_t MLX5_RCV_DBR ; 
 int /*<<< orphan*/  MLX5_RSC_TYPE_QP ; 
 size_t MLX5_SND_DBR ; 
 scalar_t__ MLX5_WQE_CTRL_CQ_UPDATE ; 
 struct mlx5_qp* calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct mlx5_qp*) ; 
 int ibv_cmd_create_qp_ex (struct ibv_context*,int /*<<< orphan*/ *,int,struct ibv_qp_init_attr_ex*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ibv_cmd_destroy_qp (struct ibv_qp*) ; 
 int /*<<< orphan*/  is_xrc_tgt (scalar_t__) ; 
 int /*<<< orphan*/  map_uuar (struct ibv_context*,struct mlx5_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_create_qp_resp_ex*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* mlx5_alloc_dbrec (struct mlx5_context*) ; 
 scalar_t__ mlx5_alloc_qp_buf (struct ibv_context*,struct ibv_qp_init_attr_ex*,struct mlx5_qp*,int) ; 
 int mlx5_calc_wq_size (struct mlx5_context*,struct ibv_qp_init_attr_ex*,struct mlx5_qp*) ; 
 int /*<<< orphan*/  mlx5_clear_uidx (struct mlx5_context*,void*) ; 
 int mlx5_cmd_create_qp_ex (struct ibv_context*,struct ibv_qp_init_attr_ex*,struct mlx5_create_qp_resp_ex*,struct mlx5_qp*,struct mlx5_create_qp_resp_ex*) ; 
 int mlx5_cmd_create_rss_qp (struct ibv_context*,struct ibv_qp_init_attr_ex*,struct mlx5_qp*) ; 
 int /*<<< orphan*/  mlx5_dbg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlx5_free_db (struct mlx5_context*,scalar_t__*) ; 
 int /*<<< orphan*/  mlx5_free_qp_buf (struct mlx5_qp*) ; 
 int /*<<< orphan*/  mlx5_init_qp_indices (struct mlx5_qp*) ; 
 scalar_t__ mlx5_spinlock_init (int /*<<< orphan*/ *) ; 
 int mlx5_store_qp (struct mlx5_context*,void*,struct mlx5_qp*) ; 
 void* mlx5_store_uidx (struct mlx5_context*,struct mlx5_qp*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ qp_sig_enabled () ; 
 struct mlx5_context* to_mctx (struct ibv_context*) ; 
 scalar_t__ use_scatter_to_cqe () ; 

__attribute__((used)) static struct ibv_qp *create_qp(struct ibv_context *context,
			 struct ibv_qp_init_attr_ex *attr)
{
	struct mlx5_create_qp		cmd;
	struct mlx5_create_qp_resp	resp;
	struct mlx5_create_qp_resp_ex resp_ex;
	struct mlx5_qp		       *qp;
	int				ret;
	struct mlx5_context	       *ctx = to_mctx(context);
	struct ibv_qp		       *ibqp;
	int32_t				usr_idx = 0;
	uint32_t			uuar_index;
	FILE *fp = ctx->dbg_fp;

	if (attr->comp_mask & ~MLX5_CREATE_QP_SUP_COMP_MASK)
		return NULL;

	if ((attr->comp_mask & IBV_QP_INIT_ATTR_MAX_TSO_HEADER) &&
	    (attr->qp_type != IBV_QPT_RAW_PACKET))
		return NULL;

	qp = calloc(1, sizeof(*qp));
	if (!qp) {
		mlx5_dbg(fp, MLX5_DBG_QP, "\n");
		return NULL;
	}
	ibqp = (struct ibv_qp *)&qp->verbs_qp;
	qp->ibv_qp = ibqp;

	memset(&cmd, 0, sizeof(cmd));
	memset(&resp, 0, sizeof(resp));
	memset(&resp_ex, 0, sizeof(resp_ex));

	if (attr->comp_mask & IBV_QP_INIT_ATTR_RX_HASH) {
		ret = mlx5_cmd_create_rss_qp(context, attr, qp);
		if (ret)
			goto err;

		return ibqp;
	}

	qp->wq_sig = qp_sig_enabled();
	if (qp->wq_sig)
		cmd.flags |= MLX5_QP_FLAG_SIGNATURE;

	if (use_scatter_to_cqe())
		cmd.flags |= MLX5_QP_FLAG_SCATTER_CQE;

	ret = mlx5_calc_wq_size(ctx, attr, qp);
	if (ret < 0) {
		errno = -ret;
		goto err;
	}

	if (attr->qp_type == IBV_QPT_RAW_PACKET) {
		qp->buf_size = qp->sq.offset;
		qp->sq_buf_size = ret - qp->buf_size;
		qp->sq.offset = 0;
	} else {
		qp->buf_size = ret;
		qp->sq_buf_size = 0;
	}

	if (mlx5_alloc_qp_buf(context, attr, qp, ret)) {
		mlx5_dbg(fp, MLX5_DBG_QP, "\n");
		goto err;
	}

	if (attr->qp_type == IBV_QPT_RAW_PACKET) {
		qp->sq_start = qp->sq_buf.buf;
		qp->sq.qend = qp->sq_buf.buf +
				(qp->sq.wqe_cnt << qp->sq.wqe_shift);
	} else {
		qp->sq_start = qp->buf.buf + qp->sq.offset;
		qp->sq.qend = qp->buf.buf + qp->sq.offset +
				(qp->sq.wqe_cnt << qp->sq.wqe_shift);
	}

	mlx5_init_qp_indices(qp);

	if (mlx5_spinlock_init(&qp->sq.lock) ||
	    mlx5_spinlock_init(&qp->rq.lock))
		goto err_free_qp_buf;

	qp->db = mlx5_alloc_dbrec(ctx);
	if (!qp->db) {
		mlx5_dbg(fp, MLX5_DBG_QP, "\n");
		goto err_free_qp_buf;
	}

	qp->db[MLX5_RCV_DBR] = 0;
	qp->db[MLX5_SND_DBR] = 0;

	cmd.buf_addr = (uintptr_t) qp->buf.buf;
	cmd.sq_buf_addr = (attr->qp_type == IBV_QPT_RAW_PACKET) ?
			  (uintptr_t) qp->sq_buf.buf : 0;
	cmd.db_addr  = (uintptr_t) qp->db;
	cmd.sq_wqe_count = qp->sq.wqe_cnt;
	cmd.rq_wqe_count = qp->rq.wqe_cnt;
	cmd.rq_wqe_shift = qp->rq.wqe_shift;

	if (ctx->atomic_cap == IBV_ATOMIC_HCA)
		qp->atomics_enabled = 1;

	if (!ctx->cqe_version) {
		cmd.uidx = 0xffffff;
		pthread_mutex_lock(&ctx->qp_table_mutex);
	} else if (!is_xrc_tgt(attr->qp_type)) {
		usr_idx = mlx5_store_uidx(ctx, qp);
		if (usr_idx < 0) {
			mlx5_dbg(fp, MLX5_DBG_QP, "Couldn't find free user index\n");
			goto err_rq_db;
		}

		cmd.uidx = usr_idx;
	}

	if (attr->comp_mask & MLX5_CREATE_QP_EX2_COMP_MASK)
		ret = mlx5_cmd_create_qp_ex(context, attr, &cmd, qp, &resp_ex);
	else
		ret = ibv_cmd_create_qp_ex(context, &qp->verbs_qp, sizeof(qp->verbs_qp),
					   attr, &cmd.ibv_cmd, sizeof(cmd),
					   &resp.ibv_resp, sizeof(resp));
	if (ret) {
		mlx5_dbg(fp, MLX5_DBG_QP, "ret %d\n", ret);
		goto err_free_uidx;
	}

	uuar_index = (attr->comp_mask & MLX5_CREATE_QP_EX2_COMP_MASK) ?
			resp_ex.uuar_index : resp.uuar_index;
	if (!ctx->cqe_version) {
		if (qp->sq.wqe_cnt || qp->rq.wqe_cnt) {
			ret = mlx5_store_qp(ctx, ibqp->qp_num, qp);
			if (ret) {
				mlx5_dbg(fp, MLX5_DBG_QP, "ret %d\n", ret);
				goto err_destroy;
			}
		}

		pthread_mutex_unlock(&ctx->qp_table_mutex);
	}

	map_uuar(context, qp, uuar_index);

	qp->rq.max_post = qp->rq.wqe_cnt;
	if (attr->sq_sig_all)
		qp->sq_signal_bits = MLX5_WQE_CTRL_CQ_UPDATE;
	else
		qp->sq_signal_bits = 0;

	attr->cap.max_send_wr = qp->sq.max_post;
	attr->cap.max_recv_wr = qp->rq.max_post;
	attr->cap.max_recv_sge = qp->rq.max_gs;

	qp->rsc.type = MLX5_RSC_TYPE_QP;
	qp->rsc.rsn = (ctx->cqe_version && !is_xrc_tgt(attr->qp_type)) ?
		      usr_idx : ibqp->qp_num;

	return ibqp;

err_destroy:
	ibv_cmd_destroy_qp(ibqp);

err_free_uidx:
	if (!ctx->cqe_version)
		pthread_mutex_unlock(&to_mctx(context)->qp_table_mutex);
	else if (!is_xrc_tgt(attr->qp_type))
		mlx5_clear_uidx(ctx, usr_idx);

err_rq_db:
	mlx5_free_db(to_mctx(context), qp->db);

err_free_qp_buf:
	mlx5_free_qp_buf(qp);

err:
	free(qp);

	return NULL;
}