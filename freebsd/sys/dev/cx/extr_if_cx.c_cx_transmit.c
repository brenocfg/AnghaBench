#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* ifp; scalar_t__ timeout; int /*<<< orphan*/  intr_action; TYPE_1__* tty; scalar_t__ atimeout; } ;
typedef  TYPE_2__ drv_t ;
struct TYPE_9__ {scalar_t__ mode; TYPE_2__* sys; } ;
typedef  TYPE_3__ cx_chan_t ;
struct TYPE_10__ {int /*<<< orphan*/  if_drv_flags; } ;
struct TYPE_7__ {int t_state; scalar_t__ t_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_WRITE ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int MY_SOFT_INTR ; 
 scalar_t__ M_ASYNC ; 
 int TS_BUSY ; 
 int TS_FLUSH ; 
 int /*<<< orphan*/  cx_fast_ih ; 
 int /*<<< orphan*/  cx_start (TYPE_2__*) ; 
 int /*<<< orphan*/  if_inc_counter (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swi_sched (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx_transmit (cx_chan_t *c, void *attachment, int len)
{
	drv_t *d = c->sys;

	if (!d)
		return;
		
	if (c->mode == M_ASYNC && d->tty) {
		d->tty->t_state &= ~(TS_BUSY | TS_FLUSH);
		d->atimeout = 0;
		if (d->tty->t_dev) {
			d->intr_action |= CX_WRITE;
			MY_SOFT_INTR = 1;
			swi_sched (cx_fast_ih, 0);
		}
		return;
	}
	d->timeout = 0;
#ifndef NETGRAPH
	if_inc_counter(d->ifp, IFCOUNTER_OPACKETS, 1);
	d->ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
#endif
	cx_start (d);
}