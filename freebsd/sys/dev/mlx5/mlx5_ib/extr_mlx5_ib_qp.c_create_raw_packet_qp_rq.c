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
struct TYPE_2__ {int /*<<< orphan*/  mqp; struct mlx5_ib_qp* container_mibqp; } ;
struct mlx5_ib_rq {TYPE_1__ base; } ;
struct mlx5_ib_qp {int flags; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
typedef  void __be64 ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (void*,void*,void*) ; 
 int MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_GET64 (void*,void*,int /*<<< orphan*/ ) ; 
 int MLX5_IB_QP_CAP_SCATTER_FCS ; 
 int MLX5_RQC_RQ_TYPE_MEMORY_RQ_INLINE ; 
 int MLX5_RQC_STATE_RST ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int MLX5_WQ_TYPE_CYCLIC ; 
 int /*<<< orphan*/  cqn ; 
 int /*<<< orphan*/  cqn_rcv ; 
 void* create_qp_in ; 
 void* create_rq_in ; 
 void* ctx ; 
 int /*<<< orphan*/  dbr_addr ; 
 int /*<<< orphan*/  end_padding_mode ; 
 int /*<<< orphan*/  flush_in_error_en ; 
 int get_rq_pas_size (void*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  log_page_size ; 
 int /*<<< orphan*/  log_rq_size ; 
 int /*<<< orphan*/  log_rq_stride ; 
 int /*<<< orphan*/  log_wq_pg_sz ; 
 int /*<<< orphan*/  log_wq_stride ; 
 int /*<<< orphan*/  log_wq_sz ; 
 int /*<<< orphan*/  mem_rq_type ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int mlx5_core_create_rq_tracked (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  page_offset ; 
 int /*<<< orphan*/  pd ; 
 void* qpc ; 
 int /*<<< orphan*/  scatter_fcs ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  user_index ; 
 int /*<<< orphan*/  vlan_strip_disable ; 
 int /*<<< orphan*/  wq_type ; 

__attribute__((used)) static int create_raw_packet_qp_rq(struct mlx5_ib_dev *dev,
				   struct mlx5_ib_rq *rq, void *qpin)
{
	struct mlx5_ib_qp *mqp = rq->base.container_mibqp;
	__be64 *pas;
	__be64 *qp_pas;
	void *in;
	void *rqc;
	void *wq;
	void *qpc = MLX5_ADDR_OF(create_qp_in, qpin, qpc);
	int inlen;
	int err;
	u32 rq_pas_size = get_rq_pas_size(qpc);

	inlen = MLX5_ST_SZ_BYTES(create_rq_in) + rq_pas_size;
	in = mlx5_vzalloc(inlen);
	if (!in)
		return -ENOMEM;

	rqc = MLX5_ADDR_OF(create_rq_in, in, ctx);
	MLX5_SET(rqc, rqc, vlan_strip_disable, 1);
	MLX5_SET(rqc, rqc, mem_rq_type, MLX5_RQC_RQ_TYPE_MEMORY_RQ_INLINE);
	MLX5_SET(rqc, rqc, state, MLX5_RQC_STATE_RST);
	MLX5_SET(rqc, rqc, flush_in_error_en, 1);
	MLX5_SET(rqc, rqc, user_index, MLX5_GET(qpc, qpc, user_index));
	MLX5_SET(rqc, rqc, cqn, MLX5_GET(qpc, qpc, cqn_rcv));

	if (mqp->flags & MLX5_IB_QP_CAP_SCATTER_FCS)
		MLX5_SET(rqc, rqc, scatter_fcs, 1);

	wq = MLX5_ADDR_OF(rqc, rqc, wq);
	MLX5_SET(wq, wq, wq_type, MLX5_WQ_TYPE_CYCLIC);
	MLX5_SET(wq, wq, end_padding_mode,
		 MLX5_GET(qpc, qpc, end_padding_mode));
	MLX5_SET(wq, wq, page_offset, MLX5_GET(qpc, qpc, page_offset));
	MLX5_SET(wq, wq, pd, MLX5_GET(qpc, qpc, pd));
	MLX5_SET64(wq, wq, dbr_addr, MLX5_GET64(qpc, qpc, dbr_addr));
	MLX5_SET(wq, wq, log_wq_stride, MLX5_GET(qpc, qpc, log_rq_stride) + 4);
	MLX5_SET(wq, wq, log_wq_pg_sz, MLX5_GET(qpc, qpc, log_page_size));
	MLX5_SET(wq, wq, log_wq_sz, MLX5_GET(qpc, qpc, log_rq_size));

	pas = (__be64 *)MLX5_ADDR_OF(wq, wq, pas);
	qp_pas = (__be64 *)MLX5_ADDR_OF(create_qp_in, qpin, pas);
	memcpy(pas, qp_pas, rq_pas_size);

	err = mlx5_core_create_rq_tracked(dev->mdev, in, inlen, &rq->base.mqp);

	kvfree(in);

	return err;
}