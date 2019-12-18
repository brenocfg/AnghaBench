#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hook_p ;
struct TYPE_6__ {int /*<<< orphan*/  hk_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_FREE_HOOK (TYPE_1__*) ; 
 scalar_t__ _NG_HOOK_NODE (TYPE_1__*) ; 
 int /*<<< orphan*/  _NG_NODE_UNREF (scalar_t__) ; 
 TYPE_1__ ng_deadhook ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

void
ng_unref_hook(hook_p hook)
{

	if (hook == &ng_deadhook)
		return;

	if (refcount_release(&hook->hk_refs)) { /* we were the last */
		if (_NG_HOOK_NODE(hook)) /* it'll probably be ng_deadnode */
			_NG_NODE_UNREF((_NG_HOOK_NODE(hook)));
		NG_FREE_HOOK(hook);
	}
}