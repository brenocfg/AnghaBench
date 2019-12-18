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
struct netmap_generic_adapter {int /*<<< orphan*/  (* save_if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ NA (struct ifnet*) ; 
 int /*<<< orphan*/  NM_NA_VALID (struct ifnet*) ; 
 int generic_rx_handler (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  nm_prlim (int,char*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
freebsd_generic_rx_handler(struct ifnet *ifp, struct mbuf *m)
{
	int stolen;

	if (unlikely(!NM_NA_VALID(ifp))) {
		nm_prlim(1, "Warning: RX packet intercepted, but no"
				" emulated adapter");
		return;
	}

	stolen = generic_rx_handler(ifp, m);
	if (!stolen) {
		struct netmap_generic_adapter *gna =
				(struct netmap_generic_adapter *)NA(ifp);
		gna->save_if_input(ifp, m);
	}
}