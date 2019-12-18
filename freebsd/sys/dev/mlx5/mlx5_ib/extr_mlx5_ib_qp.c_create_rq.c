#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  dma; } ;
struct mlx5_ib_rwq {int rq_num_pas; int user_index; int log_rq_stride; int log_rq_size; int rq_page_offset; int log_page_size; int wq_sig; int /*<<< orphan*/  core_qp; int /*<<< orphan*/  page_shift; int /*<<< orphan*/  umem; TYPE_2__ db; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_wq_init_attr {int /*<<< orphan*/  cq; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_5__ {int cqn; } ;
struct TYPE_8__ {TYPE_1__ mcq; } ;
struct TYPE_7__ {int pdn; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (void*,void*,void*) ; 
 int MLX5_RQC_RQ_TYPE_MEMORY_RQ_INLINE ; 
 int MLX5_RQC_STATE_RST ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,struct ib_pd*,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int MLX5_WQ_END_PAD_MODE_ALIGN ; 
 int MLX5_WQ_TYPE_CYCLIC ; 
 struct ib_pd* cqn ; 
 void* create_rq_in ; 
 void* ctx ; 
 int /*<<< orphan*/  dbr_addr ; 
 struct ib_pd* end_padding_mode ; 
 struct ib_pd* flush_in_error_en ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 struct ib_pd* log_wq_pg_sz ; 
 struct ib_pd* log_wq_stride ; 
 struct ib_pd* log_wq_sz ; 
 struct ib_pd* mem_rq_type ; 
 int mlx5_core_create_rq_tracked (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_populate_pas (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* mlx5_vzalloc (int) ; 
 struct ib_pd* page_offset ; 
 void* pas ; 
 struct ib_pd* state ; 
 TYPE_4__* to_mcq (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_mpd (struct ib_pd*) ; 
 struct ib_pd* user_index ; 
 struct ib_pd* wq_signature ; 
 struct ib_pd* wq_type ; 

__attribute__((used)) static int  create_rq(struct mlx5_ib_rwq *rwq, struct ib_pd *pd,
		      struct ib_wq_init_attr *init_attr)
{
	struct mlx5_ib_dev *dev;
	__be64 *rq_pas0;
	void *in;
	void *rqc;
	void *wq;
	int inlen;
	int err;

	dev = to_mdev(pd->device);

	inlen = MLX5_ST_SZ_BYTES(create_rq_in) + sizeof(u64) * rwq->rq_num_pas;
	in = mlx5_vzalloc(inlen);
	if (!in)
		return -ENOMEM;

	rqc = MLX5_ADDR_OF(create_rq_in, in, ctx);
	MLX5_SET(rqc,  rqc, mem_rq_type,
		 MLX5_RQC_RQ_TYPE_MEMORY_RQ_INLINE);
	MLX5_SET(rqc, rqc, user_index, rwq->user_index);
	MLX5_SET(rqc,  rqc, cqn, to_mcq(init_attr->cq)->mcq.cqn);
	MLX5_SET(rqc,  rqc, state, MLX5_RQC_STATE_RST);
	MLX5_SET(rqc,  rqc, flush_in_error_en, 1);
	wq = MLX5_ADDR_OF(rqc, rqc, wq);
	MLX5_SET(wq, wq, wq_type, MLX5_WQ_TYPE_CYCLIC);
	MLX5_SET(wq, wq, end_padding_mode, MLX5_WQ_END_PAD_MODE_ALIGN);
	MLX5_SET(wq, wq, log_wq_stride, rwq->log_rq_stride);
	MLX5_SET(wq, wq, log_wq_sz, rwq->log_rq_size);
	MLX5_SET(wq, wq, pd, to_mpd(pd)->pdn);
	MLX5_SET(wq, wq, page_offset, rwq->rq_page_offset);
	MLX5_SET(wq, wq, log_wq_pg_sz, rwq->log_page_size);
	MLX5_SET(wq, wq, wq_signature, rwq->wq_sig);
	MLX5_SET64(wq, wq, dbr_addr, rwq->db.dma);
	rq_pas0 = (__be64 *)MLX5_ADDR_OF(wq, wq, pas);
	mlx5_ib_populate_pas(dev, rwq->umem, rwq->page_shift, rq_pas0, 0);
	err = mlx5_core_create_rq_tracked(dev->mdev, in, inlen, &rwq->core_qp);
	kvfree(in);
	return err;
}