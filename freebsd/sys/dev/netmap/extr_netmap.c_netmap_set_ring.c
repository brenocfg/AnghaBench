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
typedef  size_t u_int ;
struct netmap_adapter {int dummy; } ;
typedef  enum txrx { ____Placeholder_txrx } txrx ;
struct TYPE_3__ {scalar_t__ nkr_stopped; } ;

/* Variables and functions */
 TYPE_1__** NMR (struct netmap_adapter*,int) ; 
 int /*<<< orphan*/  netmap_disable_ring (TYPE_1__*,int) ; 

void
netmap_set_ring(struct netmap_adapter *na, u_int ring_id, enum txrx t, int stopped)
{
	if (stopped)
		netmap_disable_ring(NMR(na, t)[ring_id], stopped);
	else
		NMR(na, t)[ring_id]->nkr_stopped = 0;
}