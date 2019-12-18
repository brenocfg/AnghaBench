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
struct ibv_cq {int dummy; } ;
struct TYPE_2__ {struct ibv_cq* (* create_cq ) (struct ibv_context*,int,struct ibv_comp_channel*,int) ;} ;
struct ibv_context {TYPE_1__ ops; } ;
struct ibv_comp_channel {int dummy; } ;

/* Variables and functions */
 struct ibv_cq* stub1 (struct ibv_context*,int,struct ibv_comp_channel*,int) ; 
 int /*<<< orphan*/  verbs_init_cq (struct ibv_cq*,struct ibv_context*,struct ibv_comp_channel*,void*) ; 

struct ibv_cq *__ibv_create_cq(struct ibv_context *context, int cqe, void *cq_context,
			       struct ibv_comp_channel *channel, int comp_vector)
{
	struct ibv_cq *cq;

	cq = context->ops.create_cq(context, cqe, channel, comp_vector);

	if (cq)
		verbs_init_cq(cq, context, channel, cq_context);

	return cq;
}