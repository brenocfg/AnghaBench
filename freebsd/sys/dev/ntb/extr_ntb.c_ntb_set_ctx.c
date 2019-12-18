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
struct ntb_ctx_ops {int /*<<< orphan*/  (* link_event ) (void*) ;} ;
struct ntb_child {int /*<<< orphan*/  ctx_lock; struct ntb_ctx_ops const* ctx_ops; void* ctx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct ntb_child* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

int
ntb_set_ctx(device_t ntb, void *ctx, const struct ntb_ctx_ops *ctx_ops)
{
	struct ntb_child *nc = device_get_ivars(ntb);

	if (ctx == NULL || ctx_ops == NULL)
		return (EINVAL);

	rm_wlock(&nc->ctx_lock);
	if (nc->ctx_ops != NULL) {
		rm_wunlock(&nc->ctx_lock);
		return (EINVAL);
	}
	nc->ctx = ctx;
	nc->ctx_ops = ctx_ops;

	/*
	 * If applicaiton driver asks for link events, generate fake one now
	 * to let it update link state without races while we hold the lock.
	 */
	if (ctx_ops->link_event != NULL)
		ctx_ops->link_event(ctx);
	rm_wunlock(&nc->ctx_lock);

	return (0);
}