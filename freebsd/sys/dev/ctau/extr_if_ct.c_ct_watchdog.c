#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  chan; scalar_t__ running; } ;
typedef  TYPE_1__ drv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CT_DEBUG (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ct_set_dtr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ct_set_rts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ct_setup_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ct_start (TYPE_1__*) ; 
 int /*<<< orphan*/  ct_start_chan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ct_watchdog (drv_t *d)
{

	CT_DEBUG (d, ("device timeout\n"));
	if (d->running) {
		ct_setup_chan (d->chan);
		ct_start_chan (d->chan, 0, 0);
		ct_set_dtr (d->chan, 1);
		ct_set_rts (d->chan, 1);
		ct_start (d);
	}
}