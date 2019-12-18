#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct mlx5e_cq_param {int /*<<< orphan*/  cqc; } ;
struct TYPE_7__ {int /*<<< orphan*/  dma; } ;
struct TYPE_10__ {int npages; int page_shift; } ;
struct TYPE_8__ {TYPE_2__ db; TYPE_5__ buf; } ;
struct mlx5_core_cq {TYPE_1__* uar; } ;
struct mlx5e_cq {TYPE_4__* priv; TYPE_3__ wq_ctrl; struct mlx5_core_cq mcq; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_9__ {int /*<<< orphan*/  doorbell_lock; int /*<<< orphan*/  mdev; } ;
struct TYPE_6__ {int index; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_GET_DOORBELL_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  c_eqn ; 
 int /*<<< orphan*/  cq_context ; 
 int /*<<< orphan*/  create_cq_in ; 
 int /*<<< orphan*/  dbr_addr ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  log_page_size ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_create_cq (int /*<<< orphan*/ ,struct mlx5_core_cq*,void*,int) ; 
 int /*<<< orphan*/  mlx5_fill_page_array (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_vector2eqn (int /*<<< orphan*/ ,int,int*,int*) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  mlx5e_cq_arm (struct mlx5e_cq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pas ; 
 int /*<<< orphan*/  uar_page ; 

__attribute__((used)) static int
mlx5e_enable_cq(struct mlx5e_cq *cq, struct mlx5e_cq_param *param, int eq_ix)
{
	struct mlx5_core_cq *mcq = &cq->mcq;
	void *in;
	void *cqc;
	int inlen;
	int irqn_not_used;
	int eqn;
	int err;

	inlen = MLX5_ST_SZ_BYTES(create_cq_in) +
	    sizeof(u64) * cq->wq_ctrl.buf.npages;
	in = mlx5_vzalloc(inlen);
	if (in == NULL)
		return (-ENOMEM);

	cqc = MLX5_ADDR_OF(create_cq_in, in, cq_context);

	memcpy(cqc, param->cqc, sizeof(param->cqc));

	mlx5_fill_page_array(&cq->wq_ctrl.buf,
	    (__be64 *) MLX5_ADDR_OF(create_cq_in, in, pas));

	mlx5_vector2eqn(cq->priv->mdev, eq_ix, &eqn, &irqn_not_used);

	MLX5_SET(cqc, cqc, c_eqn, eqn);
	MLX5_SET(cqc, cqc, uar_page, mcq->uar->index);
	MLX5_SET(cqc, cqc, log_page_size, cq->wq_ctrl.buf.page_shift -
	    PAGE_SHIFT);
	MLX5_SET64(cqc, cqc, dbr_addr, cq->wq_ctrl.db.dma);

	err = mlx5_core_create_cq(cq->priv->mdev, mcq, in, inlen);

	kvfree(in);

	if (err)
		return (err);

	mlx5e_cq_arm(cq, MLX5_GET_DOORBELL_LOCK(&cq->priv->doorbell_lock));

	return (0);
}