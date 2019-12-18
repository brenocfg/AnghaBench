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
struct kthread_desc {int /*<<< orphan*/  arg0; int /*<<< orphan*/  global_threadpp; scalar_t__ func; } ;

/* Variables and functions */
 int kthread_add (void (*) (void*),int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 

void
kthread_start(const void *udata)
{
	const struct kthread_desc	*kp = udata;
	int error;

	error = kthread_add((void (*)(void *))kp->func, NULL,
		    NULL, kp->global_threadpp, 0, 0, "%s", kp->arg0);
	if (error)
		panic("kthread_start: %s: error %d", kp->arg0, error);
}