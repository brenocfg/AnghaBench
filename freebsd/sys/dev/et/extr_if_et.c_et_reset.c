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
struct et_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ET_INTR_MASK ; 
 int /*<<< orphan*/  ET_MAC_CFG1 ; 
 int ET_MAC_CFG1_RST_RXFUNC ; 
 int ET_MAC_CFG1_RST_RXMC ; 
 int ET_MAC_CFG1_RST_TXFUNC ; 
 int ET_MAC_CFG1_RST_TXMC ; 
 int ET_MAC_CFG1_SIM_RST ; 
 int ET_MAC_CFG1_SOFT_RST ; 
 int /*<<< orphan*/  ET_SWRST ; 
 int ET_SWRST_MAC ; 
 int ET_SWRST_MAC_STAT ; 
 int ET_SWRST_MMC ; 
 int ET_SWRST_RXDMA ; 
 int ET_SWRST_RXMAC ; 
 int ET_SWRST_TXDMA ; 
 int ET_SWRST_TXMAC ; 

__attribute__((used)) static void
et_reset(struct et_softc *sc)
{

	CSR_WRITE_4(sc, ET_MAC_CFG1,
		    ET_MAC_CFG1_RST_TXFUNC | ET_MAC_CFG1_RST_RXFUNC |
		    ET_MAC_CFG1_RST_TXMC | ET_MAC_CFG1_RST_RXMC |
		    ET_MAC_CFG1_SIM_RST | ET_MAC_CFG1_SOFT_RST);

	CSR_WRITE_4(sc, ET_SWRST,
		    ET_SWRST_TXDMA | ET_SWRST_RXDMA |
		    ET_SWRST_TXMAC | ET_SWRST_RXMAC |
		    ET_SWRST_MAC | ET_SWRST_MAC_STAT | ET_SWRST_MMC);

	CSR_WRITE_4(sc, ET_MAC_CFG1,
		    ET_MAC_CFG1_RST_TXFUNC | ET_MAC_CFG1_RST_RXFUNC |
		    ET_MAC_CFG1_RST_TXMC | ET_MAC_CFG1_RST_RXMC);
	CSR_WRITE_4(sc, ET_MAC_CFG1, 0);
	/* Disable interrupts. */
	CSR_WRITE_4(sc, ET_INTR_MASK, 0xffffffff);
}