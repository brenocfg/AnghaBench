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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* ifp; scalar_t__ timeout; } ;
typedef  TYPE_1__ drv_t ;
struct TYPE_7__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ cp_chan_t ;
struct TYPE_8__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  cp_start (TYPE_1__*) ; 
 int /*<<< orphan*/  if_inc_counter (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cp_transmit (cp_chan_t *c, void *attachment, int len)
{
	drv_t *d = c->sys;

	d->timeout = 0;
#ifndef NETGRAPH
	if_inc_counter(d->ifp, IFCOUNTER_OPACKETS, 1);
	d->ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
#endif
	cp_start (d);
}