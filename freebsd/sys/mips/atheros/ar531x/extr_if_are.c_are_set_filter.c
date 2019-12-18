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
struct ifnet {int if_flags; } ;
struct are_softc {struct ifnet* are_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_HTHI ; 
 int /*<<< orphan*/  CSR_HTLO ; 
 int /*<<< orphan*/  CSR_MACCTL ; 
 int CSR_READ_4 (struct are_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct are_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_PROMISC ; 
 int MACCTL_HBD ; 
 int MACCTL_PM ; 
 int MACCTL_PR ; 

__attribute__((used)) static int
are_set_filter(struct are_softc *sc)
{
	struct ifnet	    *ifp;
	int mchash[2];
	int macctl;

	ifp = sc->are_ifp;

	macctl = CSR_READ_4(sc, CSR_MACCTL);
	macctl &= ~(MACCTL_PR | MACCTL_PM);
	macctl |= MACCTL_HBD;

	if (ifp->if_flags & IFF_PROMISC)
		macctl |= MACCTL_PR;

	/* Todo: hash table set. 
	 * But I don't know how to use multicast hash table at this soc.
	 */

	/* this is allmulti */
	mchash[0] = mchash[1] = 0xffffffff;
	macctl |= MACCTL_PM;

	CSR_WRITE_4(sc, CSR_HTLO, mchash[0]);
	CSR_WRITE_4(sc, CSR_HTHI, mchash[1]);
	CSR_WRITE_4(sc, CSR_MACCTL, macctl);

	return 0;
}