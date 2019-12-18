#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct netmap_adapter {int na_flags; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 struct netmap_adapter* NA (struct ifnet*) ; 
 int NAF_SKIP_INTR ; 
 int NM_IRQ_PASS ; 
 int netmap_common_irq (struct netmap_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_netmap_on (struct netmap_adapter*) ; 
 int /*<<< orphan*/  nm_prdis (char*) ; 

int
netmap_rx_irq(struct ifnet *ifp, u_int q, u_int *work_done)
{
	struct netmap_adapter *na = NA(ifp);

	/*
	 * XXX emulated netmap mode sets NAF_SKIP_INTR so
	 * we still use the regular driver even though the previous
	 * check fails. It is unclear whether we should use
	 * nm_native_on() here.
	 */
	if (!nm_netmap_on(na))
		return NM_IRQ_PASS;

	if (na->na_flags & NAF_SKIP_INTR) {
		nm_prdis("use regular interrupt");
		return NM_IRQ_PASS;
	}

	return netmap_common_irq(na, q, work_done);
}