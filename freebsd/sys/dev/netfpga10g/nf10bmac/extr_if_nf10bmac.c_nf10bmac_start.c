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
struct nf10bmac_softc {int dummy; } ;
struct ifnet {struct nf10bmac_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF10BMAC_LOCK (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_UNLOCK (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  nf10bmac_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
nf10bmac_start(struct ifnet *ifp)
{
	struct nf10bmac_softc *sc;

	sc = ifp->if_softc;
	NF10BMAC_LOCK(sc);
	nf10bmac_start_locked(ifp);
	NF10BMAC_UNLOCK(sc);
}