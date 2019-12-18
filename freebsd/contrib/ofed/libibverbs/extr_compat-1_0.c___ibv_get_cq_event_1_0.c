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
struct ibv_cq_1_0 {void* cq_context; } ;
struct ibv_cq {int dummy; } ;
struct ibv_comp_channel {int dummy; } ;

/* Variables and functions */
 int ibv_get_cq_event (struct ibv_comp_channel*,struct ibv_cq**,void**) ; 

int __ibv_get_cq_event_1_0(struct ibv_comp_channel *channel,
			   struct ibv_cq_1_0 **cq, void **cq_context)
{
	struct ibv_cq *real_cq;
	void *cq_ptr;
	int ret;

	ret = ibv_get_cq_event(channel, &real_cq, &cq_ptr);
	if (ret)
		return ret;

	*cq         = cq_ptr;
	*cq_context = (*cq)->cq_context;

	return 0;
}