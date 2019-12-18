#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sg_lock; int /*<<< orphan*/  sg_threadcount; TYPE_1__* sg_pool; } ;
struct TYPE_5__ {int /*<<< orphan*/  sp_name; int /*<<< orphan*/  sp_proc; } ;
typedef  TYPE_1__ SVCPOOL ;
typedef  TYPE_2__ SVCGROUP ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_add (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,struct thread**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_thread_start ; 

__attribute__((used)) static void
svc_new_thread(SVCGROUP *grp)
{
	SVCPOOL *pool = grp->sg_pool;
	struct thread *td;

	mtx_lock(&grp->sg_lock);
	grp->sg_threadcount++;
	mtx_unlock(&grp->sg_lock);
	kthread_add(svc_thread_start, grp, pool->sp_proc, &td, 0, 0,
	    "%s: service", pool->sp_name);
}