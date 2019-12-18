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
struct ifnet {struct edsc_softc* if_softc; } ;
struct edsc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_EDSC ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct edsc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 

__attribute__((used)) static void
edsc_clone_destroy(struct ifnet *ifp)
{
	struct edsc_softc	*sc = ifp->if_softc;

	/*
	 * Detach from the network interface framework.
	 */
	ether_ifdetach(ifp);

	/*
	 * Free memory occupied by ifnet and softc.
	 */
	if_free(ifp);
	free(sc, M_EDSC);
}