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
typedef  int uint32_t ;
struct et_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ET_LOOPBACK ; 
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
 int /*<<< orphan*/  ET_MII_CFG ; 
 int ET_MII_CFG_CLKRST ; 
 int /*<<< orphan*/  ET_MMC_CTRL ; 
 int ET_MMC_CTRL_ENABLE ; 

__attribute__((used)) static void
et_chip_attach(struct et_softc *sc)
{
	uint32_t val;

	/*
	 * Perform minimal initialization
	 */

	/* Disable loopback */
	CSR_WRITE_4(sc, ET_LOOPBACK, 0);

	/* Reset MAC */
	CSR_WRITE_4(sc, ET_MAC_CFG1,
		    ET_MAC_CFG1_RST_TXFUNC | ET_MAC_CFG1_RST_RXFUNC |
		    ET_MAC_CFG1_RST_TXMC | ET_MAC_CFG1_RST_RXMC |
		    ET_MAC_CFG1_SIM_RST | ET_MAC_CFG1_SOFT_RST);

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

	/* Bring MAC out of reset state */
	CSR_WRITE_4(sc, ET_MAC_CFG1, 0);

	/* Enable memory controllers */
	CSR_WRITE_4(sc, ET_MMC_CTRL, ET_MMC_CTRL_ENABLE);
}