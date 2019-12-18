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
struct clknode {int dummy; } ;
struct aw_gmacclk_sc {int dummy; } ;

/* Variables and functions */
#define  CLK_IDX_MII 129 
#define  CLK_IDX_RGMII 128 
 int /*<<< orphan*/  DEVICE_LOCK (struct aw_gmacclk_sc*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct aw_gmacclk_sc*) ; 
 int EMAC_TXC_DIV_CFG_125MHZ ; 
 int EMAC_TXC_DIV_CFG_25MHZ ; 
 int ENXIO ; 
 int /*<<< orphan*/  GMACCLK_READ (struct aw_gmacclk_sc*,int*) ; 
 int /*<<< orphan*/  GMACCLK_WRITE (struct aw_gmacclk_sc*,int) ; 
 int GMAC_CLK_PIT ; 
 int GMAC_CLK_PIT_MII ; 
 int GMAC_CLK_PIT_RGMII ; 
 int GMAC_CLK_PIT_SHIFT ; 
 int GMAC_CLK_SRC ; 
 int GMAC_CLK_SRC_MII ; 
 int GMAC_CLK_SRC_RGMII ; 
 int GMAC_CLK_SRC_SHIFT ; 
 struct aw_gmacclk_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
aw_gmacclk_set_mux(struct clknode *clk, int index)
{
	struct aw_gmacclk_sc *sc;
	uint32_t val, clk_src, pit, txc_div;
	int error;

	sc = clknode_get_softc(clk);
	error = 0;

	switch (index) {
	case CLK_IDX_MII:
		clk_src = GMAC_CLK_SRC_MII;
		pit = GMAC_CLK_PIT_MII;
		txc_div = EMAC_TXC_DIV_CFG_25MHZ;
		break;
	case CLK_IDX_RGMII:
		clk_src = GMAC_CLK_SRC_RGMII;
		pit = GMAC_CLK_PIT_RGMII;
		txc_div = EMAC_TXC_DIV_CFG_125MHZ;
		break;
	default:
		return (ENXIO);
	}

	DEVICE_LOCK(sc);
	GMACCLK_READ(sc, &val);
	val &= ~(GMAC_CLK_SRC | GMAC_CLK_PIT);
	val |= (clk_src << GMAC_CLK_SRC_SHIFT);
	val |= (pit << GMAC_CLK_PIT_SHIFT);
	GMACCLK_WRITE(sc, val);
	DEVICE_UNLOCK(sc);

	return (0);
}