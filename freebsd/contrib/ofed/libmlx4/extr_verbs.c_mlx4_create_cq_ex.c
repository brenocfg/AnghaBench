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
struct ibv_cq_init_attr_ex {int /*<<< orphan*/  flags; int /*<<< orphan*/  comp_mask; int /*<<< orphan*/  wc_flags; int /*<<< orphan*/  comp_vector; int /*<<< orphan*/  channel; int /*<<< orphan*/  cqe; } ;
struct ibv_cq_ex {int dummy; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CQ_FLAGS_EXTENDED ; 
 struct ibv_cq_ex* create_cq (struct ibv_context*,struct ibv_cq_init_attr_ex*,int /*<<< orphan*/ ) ; 

struct ibv_cq_ex *mlx4_create_cq_ex(struct ibv_context *context,
				    struct ibv_cq_init_attr_ex *cq_attr)
{
	/*
	 * Make local copy since some attributes might be adjusted
	 * for internal use.
	 */
	struct ibv_cq_init_attr_ex cq_attr_c = {.cqe = cq_attr->cqe,
						.channel = cq_attr->channel,
						.comp_vector = cq_attr->comp_vector,
						.wc_flags = cq_attr->wc_flags,
						.comp_mask = cq_attr->comp_mask,
						.flags = cq_attr->flags};

	return create_cq(context, &cq_attr_c, MLX4_CQ_FLAGS_EXTENDED);
}