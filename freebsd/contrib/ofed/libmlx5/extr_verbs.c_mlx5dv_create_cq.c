#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5dv_cq_init_attr {int dummy; } ;
struct ibv_cq_init_attr_ex {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  channel; } ;
struct ibv_cq_ex {int dummy; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CQ_FLAGS_EXTENDED ; 
 struct ibv_cq_ex* create_cq (struct ibv_context*,struct ibv_cq_init_attr_ex*,int /*<<< orphan*/ ,struct mlx5dv_cq_init_attr*) ; 
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 int /*<<< orphan*/  verbs_init_cq (int /*<<< orphan*/ ,struct ibv_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ibv_cq_ex *mlx5dv_create_cq(struct ibv_context *context,
				      struct ibv_cq_init_attr_ex *cq_attr,
				      struct mlx5dv_cq_init_attr *mlx5_cq_attr)
{
	struct ibv_cq_ex *cq;

	cq = create_cq(context, cq_attr, MLX5_CQ_FLAGS_EXTENDED, mlx5_cq_attr);
	if (!cq)
		return NULL;

	verbs_init_cq(ibv_cq_ex_to_cq(cq), context,
		      cq_attr->channel, cq_attr->cq_context);
	return cq;
}