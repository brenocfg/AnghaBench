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
struct TYPE_2__ {int /*<<< orphan*/ * pm_callback; } ;

/* Variables and functions */
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 TYPE_1__* callout_msg ; 
 int /*<<< orphan*/  callout_proc_msg ; 
 int /*<<< orphan*/  mtx_callout ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
callout_system_init(void *arg)
{
	mtx_init(&mtx_callout, "callout-mtx", NULL, MTX_DEF | MTX_RECURSE);

	callout_msg[0].pm_callback = &callout_proc_msg;
	callout_msg[1].pm_callback = &callout_proc_msg;
}