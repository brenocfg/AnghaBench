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
struct ifnet {scalar_t__ if_alloctype; int /*<<< orphan*/ * if_addr; int /*<<< orphan*/  if_dname; } ;
struct hn_softc {struct ifnet* hn_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ IFT_ETHER ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet const*) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
hn_ismyvf(const struct hn_softc *sc, const struct ifnet *ifp)
{
	const struct ifnet *hn_ifp;

	hn_ifp = sc->hn_ifp;

	if (ifp == hn_ifp)
		return (false);

	if (ifp->if_alloctype != IFT_ETHER)
		return (false);

	/* Ignore lagg/vlan interfaces */
	if (strcmp(ifp->if_dname, "lagg") == 0 ||
	    strcmp(ifp->if_dname, "vlan") == 0)
		return (false);

	/*
	 * During detach events ifp->if_addr might be NULL.
	 * Make sure the bcmp() below doesn't panic on that:
	 */
	if (ifp->if_addr == NULL || hn_ifp->if_addr == NULL)
		return (false);

	if (bcmp(IF_LLADDR(ifp), IF_LLADDR(hn_ifp), ETHER_ADDR_LEN) != 0)
		return (false);

	return (true);
}