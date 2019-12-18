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
struct ibv_cq_init_attr_ex {int dummy; } ;
struct ibv_cq_ex {int dummy; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CQ_FLAGS_EXTENDED ; 
 struct ibv_cq_ex* create_cq (struct ibv_context*,struct ibv_cq_init_attr_ex*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct ibv_cq_ex *mlx5_create_cq_ex(struct ibv_context *context,
				    struct ibv_cq_init_attr_ex *cq_attr)
{
	return create_cq(context, cq_attr, MLX5_CQ_FLAGS_EXTENDED, NULL);
}