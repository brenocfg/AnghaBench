#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct mlx5e_sq_param {int /*<<< orphan*/  sqc; } ;
struct TYPE_14__ {int npages; int page_shift; } ;
struct TYPE_11__ {int /*<<< orphan*/  dma; } ;
struct TYPE_12__ {TYPE_7__ buf; TYPE_4__ db; } ;
struct TYPE_10__ {int index; } ;
struct TYPE_8__ {int cqn; } ;
struct TYPE_9__ {TYPE_1__ mcq; } ;
struct mlx5e_sq {int /*<<< orphan*/  sqn; TYPE_6__* priv; TYPE_5__ wq_ctrl; TYPE_3__ uar; TYPE_2__ cq; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_13__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (void*,void*,void*) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_SQC_STATE_RST ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int MLX5_WQ_TYPE_CYCLIC ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  cqn ; 
 void* create_sq_in ; 
 void* ctx ; 
 int /*<<< orphan*/  dbr_addr ; 
 int /*<<< orphan*/  flush_in_error_en ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  log_wq_pg_sz ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_create_sq (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fill_page_array (TYPE_7__*,int /*<<< orphan*/ *) ; 
 void* mlx5_vzalloc (int) ; 
 void* pas ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  tis_lst_sz ; 
 int /*<<< orphan*/  tis_num_0 ; 
 int /*<<< orphan*/  uar_page ; 
 int /*<<< orphan*/  wq_type ; 

int
mlx5e_enable_sq(struct mlx5e_sq *sq, struct mlx5e_sq_param *param,
    int tis_num)
{
	void *in;
	void *sqc;
	void *wq;
	int inlen;
	int err;

	inlen = MLX5_ST_SZ_BYTES(create_sq_in) +
	    sizeof(u64) * sq->wq_ctrl.buf.npages;
	in = mlx5_vzalloc(inlen);
	if (in == NULL)
		return (-ENOMEM);

	sqc = MLX5_ADDR_OF(create_sq_in, in, ctx);
	wq = MLX5_ADDR_OF(sqc, sqc, wq);

	memcpy(sqc, param->sqc, sizeof(param->sqc));

	MLX5_SET(sqc, sqc, tis_num_0, tis_num);
	MLX5_SET(sqc, sqc, cqn, sq->cq.mcq.cqn);
	MLX5_SET(sqc, sqc, state, MLX5_SQC_STATE_RST);
	MLX5_SET(sqc, sqc, tis_lst_sz, 1);
	MLX5_SET(sqc, sqc, flush_in_error_en, 1);

	MLX5_SET(wq, wq, wq_type, MLX5_WQ_TYPE_CYCLIC);
	MLX5_SET(wq, wq, uar_page, sq->uar.index);
	MLX5_SET(wq, wq, log_wq_pg_sz, sq->wq_ctrl.buf.page_shift -
	    PAGE_SHIFT);
	MLX5_SET64(wq, wq, dbr_addr, sq->wq_ctrl.db.dma);

	mlx5_fill_page_array(&sq->wq_ctrl.buf,
	    (__be64 *) MLX5_ADDR_OF(wq, wq, pas));

	err = mlx5_core_create_sq(sq->priv->mdev, in, inlen, &sq->sqn);

	kvfree(in);

	return (err);
}