#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx5_wq_param {int /*<<< orphan*/  buf_numa_node; int /*<<< orphan*/  db_numa_node; scalar_t__ linear; } ;
struct TYPE_6__ {int /*<<< orphan*/  db; } ;
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
struct TYPE_7__ {TYPE_1__ direct; } ;
struct mlx5_wq_ctrl {TYPE_2__ db; struct mlx5_core_dev* mdev; TYPE_4__ buf; } ;
struct mlx5_cqwq {int log_sz; int sz_m1; int /*<<< orphan*/  db; int /*<<< orphan*/  buf; void* log_stride; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int INT_MAX ; 
 void* MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqe_sz ; 
 int /*<<< orphan*/  log_cq_size ; 
 int mlx5_buf_alloc_node (struct mlx5_core_dev*,int /*<<< orphan*/ ,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_cqwq_get_byte_size (struct mlx5_cqwq*) ; 
 int mlx5_db_alloc_node (struct mlx5_core_dev*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_db_free (struct mlx5_core_dev*,TYPE_2__*) ; 

int mlx5_cqwq_create(struct mlx5_core_dev *mdev, struct mlx5_wq_param *param,
		     void *cqc, struct mlx5_cqwq *wq,
		     struct mlx5_wq_ctrl *wq_ctrl)
{
	int max_direct = param->linear ? INT_MAX : 0;
	int err;

	wq->log_stride = 6 + MLX5_GET(cqc, cqc, cqe_sz);
	wq->log_sz = MLX5_GET(cqc, cqc, log_cq_size);
	wq->sz_m1 = (1 << wq->log_sz) - 1;

	err = mlx5_db_alloc_node(mdev, &wq_ctrl->db, param->db_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_db_alloc() failed, %d\n", err);
		return err;
	}

	err = mlx5_buf_alloc_node(mdev, mlx5_cqwq_get_byte_size(wq),
				  max_direct, &wq_ctrl->buf,
				  param->buf_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_buf_alloc() failed, %d\n", err);
		goto err_db_free;
	}

	wq->buf = wq_ctrl->buf.direct.buf;
	wq->db  = wq_ctrl->db.db;

	wq_ctrl->mdev = mdev;

	return 0;

err_db_free:
	mlx5_db_free(mdev, &wq_ctrl->db);

	return err;
}