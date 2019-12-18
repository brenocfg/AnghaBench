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
struct TYPE_4__ {int /*<<< orphan*/  timeout_handle; scalar_t__ running; int /*<<< orphan*/  chan; } ;
typedef  TYPE_1__ drv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_DEBUG (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_set_dtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_rts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cp_down (drv_t *d)
{
	CP_DEBUG (d, ("cp_down\n"));
	/* Interface is going down -- stop it. */
	cp_set_dtr (d->chan, 0);
	cp_set_rts (d->chan, 0);

	d->running = 0;
	callout_stop (&d->timeout_handle);
}