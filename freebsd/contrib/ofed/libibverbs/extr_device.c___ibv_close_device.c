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
struct verbs_device {TYPE_1__* ops; } ;
struct verbs_context {struct verbs_context* priv; } ;
struct ibv_context {int async_fd; int cmd_fd; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_context ) (struct ibv_context*) ;int /*<<< orphan*/  (* uninit_context ) (struct verbs_device*,struct ibv_context*) ;} ;

/* Variables and functions */
 int abi_ver ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct verbs_context*) ; 
 int /*<<< orphan*/  stub1 (struct verbs_device*,struct ibv_context*) ; 
 int /*<<< orphan*/  stub2 (struct ibv_context*) ; 
 struct verbs_context* verbs_get_ctx (struct ibv_context*) ; 
 struct verbs_device* verbs_get_device (int /*<<< orphan*/ ) ; 

int __ibv_close_device(struct ibv_context *context)
{
	int async_fd = context->async_fd;
	int cmd_fd   = context->cmd_fd;
	int cq_fd    = -1;
	struct verbs_context *context_ex;
	struct verbs_device *verbs_device = verbs_get_device(context->device);

	context_ex = verbs_get_ctx(context);
	if (context_ex) {
		verbs_device->ops->uninit_context(verbs_device, context);
		free(context_ex->priv);
		free(context_ex);
	} else {
		verbs_device->ops->free_context(context);
	}

	close(async_fd);
	close(cmd_fd);
	if (abi_ver <= 2)
		close(cq_fd);

	return 0;
}