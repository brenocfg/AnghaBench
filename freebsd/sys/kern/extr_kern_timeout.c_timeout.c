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
typedef  int /*<<< orphan*/  timeout_t ;
struct callout_handle {struct callout* callout; } ;
struct callout_cpu {int /*<<< orphan*/  cc_callfree; } ;
struct callout {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sle; } ;

/* Variables and functions */
 struct callout_cpu* CC_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CC_LOCK (struct callout_cpu*) ; 
 int /*<<< orphan*/  CC_UNLOCK (struct callout_cpu*) ; 
 struct callout* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ c_links ; 
 int /*<<< orphan*/  callout_reset (struct callout*,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  timeout_cpu ; 

struct callout_handle
timeout(timeout_t *ftn, void *arg, int to_ticks)
{
	struct callout_cpu *cc;
	struct callout *new;
	struct callout_handle handle;

	cc = CC_CPU(timeout_cpu);
	CC_LOCK(cc);
	/* Fill in the next free callout structure. */
	new = SLIST_FIRST(&cc->cc_callfree);
	if (new == NULL)
		/* XXX Attempt to malloc first */
		panic("timeout table full");
	SLIST_REMOVE_HEAD(&cc->cc_callfree, c_links.sle);
	callout_reset(new, to_ticks, ftn, arg);
	handle.callout = new;
	CC_UNLOCK(cc);

	return (handle);
}