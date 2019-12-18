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
typedef  scalar_t__ uint64_t ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {scalar_t__ latecol; scalar_t__ ecol; scalar_t__ cexterr; scalar_t__ mpc; scalar_t__ roc; scalar_t__ ruc; scalar_t__ algnerrc; scalar_t__ crcerrs; scalar_t__ rxerrc; scalar_t__ colc; } ;
struct adapter {scalar_t__ watchdog_events; TYPE_1__ stats; scalar_t__ dropped_pkts; } ;
typedef  int ift_counter ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
#define  IFCOUNTER_COLLISIONS 130 
#define  IFCOUNTER_IERRORS 129 
#define  IFCOUNTER_OERRORS 128 
 scalar_t__ if_get_counter_default (struct ifnet*,int) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
em_if_get_counter(if_ctx_t ctx, ift_counter cnt)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct ifnet *ifp = iflib_get_ifp(ctx);

	switch (cnt) {
	case IFCOUNTER_COLLISIONS:
		return (adapter->stats.colc);
	case IFCOUNTER_IERRORS:
		return (adapter->dropped_pkts + adapter->stats.rxerrc +
		    adapter->stats.crcerrs + adapter->stats.algnerrc +
		    adapter->stats.ruc + adapter->stats.roc +
		    adapter->stats.mpc + adapter->stats.cexterr);
	case IFCOUNTER_OERRORS:
		return (adapter->stats.ecol + adapter->stats.latecol +
		    adapter->watchdog_events);
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}