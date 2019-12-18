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
struct llan_softc {int /*<<< orphan*/  unit; int /*<<< orphan*/  io_lock; struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_MULTICAST_CTRL ; 
 int /*<<< orphan*/  LLAN_CLEAR_MULTICAST ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct llan_softc*) ; 
 int /*<<< orphan*/  llan_set_maddr ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phyp_hcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
llan_set_multicast(struct llan_softc *sc)
{
	struct ifnet *ifp = sc->ifp;

	mtx_assert(&sc->io_lock, MA_OWNED);

	phyp_hcall(H_MULTICAST_CTRL, sc->unit, LLAN_CLEAR_MULTICAST, 0);

	if_foreach_llmaddr(ifp, llan_set_maddr, sc);

	return (0);
}