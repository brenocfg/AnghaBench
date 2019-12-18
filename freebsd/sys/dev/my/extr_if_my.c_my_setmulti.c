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
typedef  int u_int32_t ;
struct my_softc {struct ifnet* my_ifp; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int CSR_READ_4 (struct my_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct my_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MY_AM ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int /*<<< orphan*/  MY_MAR0 ; 
 int /*<<< orphan*/  MY_MAR1 ; 
 int /*<<< orphan*/  MY_TCRRCR ; 
 scalar_t__ if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  my_hash_maddr ; 

__attribute__((used)) static void
my_setmulti(struct my_softc * sc)
{
	struct ifnet   *ifp;
	u_int32_t       hashes[2] = {0, 0};
	u_int32_t       rxfilt;

	MY_LOCK_ASSERT(sc);

	ifp = sc->my_ifp;

	rxfilt = CSR_READ_4(sc, MY_TCRRCR);

	if (ifp->if_flags & IFF_ALLMULTI || ifp->if_flags & IFF_PROMISC) {
		rxfilt |= MY_AM;
		CSR_WRITE_4(sc, MY_TCRRCR, rxfilt);
		CSR_WRITE_4(sc, MY_MAR0, 0xFFFFFFFF);
		CSR_WRITE_4(sc, MY_MAR1, 0xFFFFFFFF);

		return;
	}
	/* first, zot all the existing hash bits */
	CSR_WRITE_4(sc, MY_MAR0, 0);
	CSR_WRITE_4(sc, MY_MAR1, 0);

	/* now program new ones */
	if (if_foreach_llmaddr(ifp, my_hash_maddr, hashes) > 0)
		rxfilt |= MY_AM;
	else
		rxfilt &= ~MY_AM;
	CSR_WRITE_4(sc, MY_MAR0, hashes[0]);
	CSR_WRITE_4(sc, MY_MAR1, hashes[1]);
	CSR_WRITE_4(sc, MY_TCRRCR, rxfilt);
}