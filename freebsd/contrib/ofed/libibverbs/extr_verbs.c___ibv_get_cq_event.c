#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ibv_cq {TYPE_1__* context; void* cq_context; } ;
struct ibv_comp_event {scalar_t__ cq_handle; } ;
struct ibv_comp_channel {int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cq_event ) (struct ibv_cq*) ;} ;
struct TYPE_3__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int read (int /*<<< orphan*/ ,struct ibv_comp_event*,int) ; 
 int /*<<< orphan*/  stub1 (struct ibv_cq*) ; 

int __ibv_get_cq_event(struct ibv_comp_channel *channel,
		       struct ibv_cq **cq, void **cq_context)
{
	struct ibv_comp_event ev;

	if (read(channel->fd, &ev, sizeof ev) != sizeof ev)
		return -1;

	*cq         = (struct ibv_cq *) (uintptr_t) ev.cq_handle;
	*cq_context = (*cq)->cq_context;

	if ((*cq)->context->ops.cq_event)
		(*cq)->context->ops.cq_event(*cq);

	return 0;
}