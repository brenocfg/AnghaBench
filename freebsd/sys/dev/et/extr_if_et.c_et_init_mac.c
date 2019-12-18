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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct ifnet {int /*<<< orphan*/  if_mtu; } ;
struct et_softc {struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int ET_FRAMELEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_IPG ; 
 int ET_IPG_B2B_SHIFT ; 
 int ET_IPG_MINIFG_SHIFT ; 
 int ET_IPG_NONB2B_1_SHIFT ; 
 int ET_IPG_NONB2B_2_SHIFT ; 
 int /*<<< orphan*/  ET_MAC_ADDR1 ; 
 int /*<<< orphan*/  ET_MAC_ADDR2 ; 
 int /*<<< orphan*/  ET_MAC_CFG1 ; 
 int ET_MAC_CFG1_RST_RXFUNC ; 
 int ET_MAC_CFG1_RST_RXMC ; 
 int ET_MAC_CFG1_RST_TXFUNC ; 
 int ET_MAC_CFG1_RST_TXMC ; 
 int ET_MAC_CFG1_SIM_RST ; 
 int ET_MAC_CFG1_SOFT_RST ; 
 int /*<<< orphan*/  ET_MAC_CTRL ; 
 int /*<<< orphan*/  ET_MAC_HDX ; 
 int ET_MAC_HDX_ALT_BEB_TRUNC_SHIFT ; 
 int ET_MAC_HDX_COLLWIN_SHIFT ; 
 int ET_MAC_HDX_EXC_DEFER ; 
 int ET_MAC_HDX_REXMIT_MAX_SHIFT ; 
 int /*<<< orphan*/  ET_MAX_FRMLEN ; 
 int /*<<< orphan*/  ET_MII_CFG ; 
 int ET_MII_CFG_CLKRST ; 
 int* IF_LLADDR (struct ifnet*) ; 

__attribute__((used)) static void
et_init_mac(struct et_softc *sc)
{
	struct ifnet *ifp;
	const uint8_t *eaddr;
	uint32_t val;

	/* Reset MAC */
	CSR_WRITE_4(sc, ET_MAC_CFG1,
		    ET_MAC_CFG1_RST_TXFUNC | ET_MAC_CFG1_RST_RXFUNC |
		    ET_MAC_CFG1_RST_TXMC | ET_MAC_CFG1_RST_RXMC |
		    ET_MAC_CFG1_SIM_RST | ET_MAC_CFG1_SOFT_RST);

	/*
	 * Setup inter packet gap
	 */
	val = (56 << ET_IPG_NONB2B_1_SHIFT) |
	    (88 << ET_IPG_NONB2B_2_SHIFT) |
	    (80 << ET_IPG_MINIFG_SHIFT) |
	    (96 << ET_IPG_B2B_SHIFT);
	CSR_WRITE_4(sc, ET_IPG, val);

	/*
	 * Setup half duplex mode
	 */
	val = (10 << ET_MAC_HDX_ALT_BEB_TRUNC_SHIFT) |
	    (15 << ET_MAC_HDX_REXMIT_MAX_SHIFT) |
	    (55 << ET_MAC_HDX_COLLWIN_SHIFT) |
	    ET_MAC_HDX_EXC_DEFER;
	CSR_WRITE_4(sc, ET_MAC_HDX, val);

	/* Clear MAC control */
	CSR_WRITE_4(sc, ET_MAC_CTRL, 0);

	/* Reset MII */
	CSR_WRITE_4(sc, ET_MII_CFG, ET_MII_CFG_CLKRST);

	/*
	 * Set MAC address
	 */
	ifp = sc->ifp;
	eaddr = IF_LLADDR(ifp);
	val = eaddr[2] | (eaddr[3] << 8) | (eaddr[4] << 16) | (eaddr[5] << 24);
	CSR_WRITE_4(sc, ET_MAC_ADDR1, val);
	val = (eaddr[0] << 16) | (eaddr[1] << 24);
	CSR_WRITE_4(sc, ET_MAC_ADDR2, val);

	/* Set max frame length */
	CSR_WRITE_4(sc, ET_MAX_FRMLEN, ET_FRAMELEN(ifp->if_mtu));

	/* Bring MAC out of reset state */
	CSR_WRITE_4(sc, ET_MAC_CFG1, 0);
}