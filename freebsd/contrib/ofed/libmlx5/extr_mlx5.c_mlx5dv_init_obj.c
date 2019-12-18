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
typedef  int uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_6__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_5__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_8__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct mlx5dv_obj {TYPE_3__ rwq; TYPE_2__ srq; TYPE_1__ cq; TYPE_4__ qp; } ;

/* Variables and functions */
 int MLX5DV_OBJ_CQ ; 
 int MLX5DV_OBJ_QP ; 
 int MLX5DV_OBJ_RWQ ; 
 int MLX5DV_OBJ_SRQ ; 
 int mlx5dv_get_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5dv_get_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5dv_get_rwq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5dv_get_srq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5dv_init_obj(struct mlx5dv_obj *obj, uint64_t obj_type)
{
	int ret = 0;

	if (obj_type & MLX5DV_OBJ_QP)
		ret = mlx5dv_get_qp(obj->qp.in, obj->qp.out);
	if (!ret && (obj_type & MLX5DV_OBJ_CQ))
		ret = mlx5dv_get_cq(obj->cq.in, obj->cq.out);
	if (!ret && (obj_type & MLX5DV_OBJ_SRQ))
		ret = mlx5dv_get_srq(obj->srq.in, obj->srq.out);
	if (!ret && (obj_type & MLX5DV_OBJ_RWQ))
		ret = mlx5dv_get_rwq(obj->rwq.in, obj->rwq.out);

	return ret;
}