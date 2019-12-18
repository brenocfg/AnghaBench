#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ v_count; int /*<<< orphan*/  v_usecount; } ;
typedef  TYPE_1__ vnode_t ;
typedef  int /*<<< orphan*/  taskq_t ;
typedef  int /*<<< orphan*/  task_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ refcount_release_if_not_last (int /*<<< orphan*/ *) ; 
 scalar_t__ taskq_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vrele ; 

void
vn_rele_async(vnode_t *vp, taskq_t *taskq)
{
	VERIFY(vp->v_count > 0);
	if (refcount_release_if_not_last(&vp->v_usecount)) {
		return;
	}
	VERIFY(taskq_dispatch((taskq_t *)taskq,
	    (task_func_t *)vrele, vp, TQ_SLEEP) != 0);
}