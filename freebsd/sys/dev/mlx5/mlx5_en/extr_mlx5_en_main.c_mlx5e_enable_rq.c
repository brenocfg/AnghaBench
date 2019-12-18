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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5e_rq_param {int /*<<< orphan*/  rqc; } ;
struct TYPE_12__ {int npages; int page_shift; } ;
struct TYPE_10__ {int /*<<< orphan*/  dma; } ;
struct TYPE_11__ {TYPE_6__ buf; TYPE_4__ db; } ;
struct mlx5e_rq {int /*<<< orphan*/  rqn; TYPE_5__ wq_ctrl; struct mlx5e_channel* channel; } ;
struct mlx5e_priv {int counter_set_id; struct mlx5_core_dev* mdev; } ;
struct TYPE_7__ {int cqn; } ;
struct TYPE_8__ {TYPE_1__ mcq; } ;
struct TYPE_9__ {TYPE_2__ cq; } ;
struct mlx5e_channel {TYPE_3__ rq; struct mlx5e_priv* priv; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (void*,void*,void*) ; 
 int MLX5_RQC_STATE_RST ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  counter_set_id ; 
 int /*<<< orphan*/  cqn ; 
 void* create_rq_in ; 
 void* ctx ; 
 int /*<<< orphan*/  dbr_addr ; 
 int /*<<< orphan*/  flush_in_error_en ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  log_wq_pg_sz ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_create_rq (struct mlx5_core_dev*,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fill_page_array (TYPE_6__*,int /*<<< orphan*/ *) ; 
 void* mlx5_vzalloc (int) ; 
 void* pas ; 
 int /*<<< orphan*/  state ; 

__attribute__((used)) static int
mlx5e_enable_rq(struct mlx5e_rq *rq, struct mlx5e_rq_param *param)
{
	struct mlx5e_channel *c = rq->channel;
	struct mlx5e_priv *priv = c->priv;
	struct mlx5_core_dev *mdev = priv->mdev;

	void *in;
	void *rqc;
	void *wq;
	int inlen;
	int err;

	inlen = MLX5_ST_SZ_BYTES(create_rq_in) +
	    sizeof(u64) * rq->wq_ctrl.buf.npages;
	in = mlx5_vzalloc(inlen);
	if (in == NULL)
		return (-ENOMEM);

	rqc = MLX5_ADDR_OF(create_rq_in, in, ctx);
	wq = MLX5_ADDR_OF(rqc, rqc, wq);

	memcpy(rqc, param->rqc, sizeof(param->rqc));

	MLX5_SET(rqc, rqc, cqn, c->rq.cq.mcq.cqn);
	MLX5_SET(rqc, rqc, state, MLX5_RQC_STATE_RST);
	MLX5_SET(rqc, rqc, flush_in_error_en, 1);
	if (priv->counter_set_id >= 0)
		MLX5_SET(rqc, rqc, counter_set_id, priv->counter_set_id);
	MLX5_SET(wq, wq, log_wq_pg_sz, rq->wq_ctrl.buf.page_shift -
	    PAGE_SHIFT);
	MLX5_SET64(wq, wq, dbr_addr, rq->wq_ctrl.db.dma);

	mlx5_fill_page_array(&rq->wq_ctrl.buf,
	    (__be64 *) MLX5_ADDR_OF(wq, wq, pas));

	err = mlx5_core_create_rq(mdev, in, inlen, &rq->rqn);

	kvfree(in);

	return (err);
}