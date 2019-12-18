#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timeout_t ;
struct callout_handle {TYPE_1__* callout; } ;
struct callout_cpu {int dummy; } ;
struct TYPE_3__ {void* c_arg; int /*<<< orphan*/ * c_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_UNLOCK (struct callout_cpu*) ; 
 struct callout_cpu* callout_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  callout_stop (TYPE_1__*) ; 

void
untimeout(timeout_t *ftn, void *arg, struct callout_handle handle)
{
	struct callout_cpu *cc;

	/*
	 * Check for a handle that was initialized
	 * by callout_handle_init, but never used
	 * for a real timeout.
	 */
	if (handle.callout == NULL)
		return;

	cc = callout_lock(handle.callout);
	if (handle.callout->c_func == ftn && handle.callout->c_arg == arg)
		callout_stop(handle.callout);
	CC_UNLOCK(cc);
}