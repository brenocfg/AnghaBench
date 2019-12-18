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
 int /*<<< orphan*/  CP_DEBUG (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cp_set_dtr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cp_set_rts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cp_start (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_start_chan (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_start_e1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_stop_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_stop_e1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cp_watchdog (drv_t *d)
{
	CP_DEBUG (d, ("device timeout\n"));
	if (d->running) {
		cp_stop_chan (d->chan);
		cp_stop_e1 (d->chan);
		cp_start_e1 (d->chan);
		cp_start_chan (d->chan, 1, 1, 0, 0);
		cp_set_dtr (d->chan, 1);
		cp_set_rts (d->chan, 1);
		cp_start (d);
	}
}