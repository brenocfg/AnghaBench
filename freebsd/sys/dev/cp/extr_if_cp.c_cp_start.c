#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  timeout_handle; TYPE_3__* chan; scalar_t__ running; } ;
typedef  TYPE_1__ drv_t ;
struct TYPE_8__ {int /*<<< orphan*/  rts; int /*<<< orphan*/  dtr; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cp_send (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_set_dtr (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cp_set_rts (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cp_watchdog_timer ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void cp_start (drv_t *d)
{
	if (d->running) {
		if (! d->chan->dtr)
			cp_set_dtr (d->chan, 1);
		if (! d->chan->rts)
			cp_set_rts (d->chan, 1);
		cp_send (d);
		callout_reset (&d->timeout_handle, hz, cp_watchdog_timer, d);
	}
}