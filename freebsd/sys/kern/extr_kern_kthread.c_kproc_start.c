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
struct kproc_desc {int /*<<< orphan*/  arg0; int /*<<< orphan*/  global_procpp; scalar_t__ func; } ;

/* Variables and functions */
 int kproc_create (void (*) (void*),int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 

void
kproc_start(const void *udata)
{
	const struct kproc_desc	*kp = udata;
	int error;

	error = kproc_create((void (*)(void *))kp->func, NULL,
		    kp->global_procpp, 0, 0, "%s", kp->arg0);
	if (error)
		panic("kproc_start: %s: error %d", kp->arg0, error);
}