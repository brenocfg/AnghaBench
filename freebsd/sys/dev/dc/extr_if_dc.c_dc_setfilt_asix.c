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
typedef  int /*<<< orphan*/  uint32_t ;
struct ifnet {int if_flags; } ;
struct dc_softc {struct ifnet* dc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_AX_FILTDATA ; 
 int /*<<< orphan*/  DC_AX_FILTIDX ; 
 int /*<<< orphan*/  DC_AX_FILTIDX_MAR0 ; 
 int /*<<< orphan*/  DC_AX_FILTIDX_MAR1 ; 
 int /*<<< orphan*/  DC_AX_FILTIDX_PAR0 ; 
 int /*<<< orphan*/  DC_AX_FILTIDX_PAR1 ; 
 int /*<<< orphan*/  DC_AX_NETCFG_RX_BROAD ; 
 int /*<<< orphan*/  DC_CLRBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_NETCFG ; 
 int /*<<< orphan*/  DC_NETCFG_RX_ALLMULTI ; 
 int /*<<< orphan*/  DC_NETCFG_RX_PROMISC ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_hash_maddr_admtek_be ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dc_setfilt_asix(struct dc_softc *sc)
{
	uint32_t eaddr[(ETHER_ADDR_LEN+3)/4];
	struct ifnet *ifp;
	uint32_t hashes[2] = { 0, 0 };

	ifp = sc->dc_ifp;

	/* Init our MAC address. */
	bcopy(IF_LLADDR(sc->dc_ifp), eaddr, ETHER_ADDR_LEN);
	CSR_WRITE_4(sc, DC_AX_FILTIDX, DC_AX_FILTIDX_PAR0);
	CSR_WRITE_4(sc, DC_AX_FILTDATA, eaddr[0]);
	CSR_WRITE_4(sc, DC_AX_FILTIDX, DC_AX_FILTIDX_PAR1);
	CSR_WRITE_4(sc, DC_AX_FILTDATA, eaddr[1]);

	/* If we want promiscuous mode, set the allframes bit. */
	if (ifp->if_flags & IFF_PROMISC)
		DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_RX_PROMISC);
	else
		DC_CLRBIT(sc, DC_NETCFG, DC_NETCFG_RX_PROMISC);

	if (ifp->if_flags & IFF_ALLMULTI)
		DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_RX_ALLMULTI);
	else
		DC_CLRBIT(sc, DC_NETCFG, DC_NETCFG_RX_ALLMULTI);

	/*
	 * The ASIX chip has a special bit to enable reception
	 * of broadcast frames.
	 */
	if (ifp->if_flags & IFF_BROADCAST)
		DC_SETBIT(sc, DC_NETCFG, DC_AX_NETCFG_RX_BROAD);
	else
		DC_CLRBIT(sc, DC_NETCFG, DC_AX_NETCFG_RX_BROAD);

	/* first, zot all the existing hash bits */
	CSR_WRITE_4(sc, DC_AX_FILTIDX, DC_AX_FILTIDX_MAR0);
	CSR_WRITE_4(sc, DC_AX_FILTDATA, 0);
	CSR_WRITE_4(sc, DC_AX_FILTIDX, DC_AX_FILTIDX_MAR1);
	CSR_WRITE_4(sc, DC_AX_FILTDATA, 0);

	/*
	 * If we're already in promisc or allmulti mode, we
	 * don't have to bother programming the multicast filter.
	 */
	if (ifp->if_flags & (IFF_PROMISC | IFF_ALLMULTI))
		return;

	/* now program new ones */
	if_foreach_llmaddr(ifp, dc_hash_maddr_admtek_be, hashes);

	CSR_WRITE_4(sc, DC_AX_FILTIDX, DC_AX_FILTIDX_MAR0);
	CSR_WRITE_4(sc, DC_AX_FILTDATA, hashes[0]);
	CSR_WRITE_4(sc, DC_AX_FILTIDX, DC_AX_FILTIDX_MAR1);
	CSR_WRITE_4(sc, DC_AX_FILTDATA, hashes[1]);
}