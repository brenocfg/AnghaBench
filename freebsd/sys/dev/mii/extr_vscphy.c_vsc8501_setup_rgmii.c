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
struct vscphy_softc {scalar_t__ contype; int txdelay; int rxdelay; scalar_t__ laneswap; } ;

/* Variables and functions */
 scalar_t__ MII_CONTYPE_RGMII_ID ; 
 scalar_t__ MII_CONTYPE_RGMII_RXID ; 
 scalar_t__ MII_CONTYPE_RGMII_TXID ; 
 int /*<<< orphan*/  VSC8501_EXTPAGE_REG ; 
 int VSC8501_RGMII_CTRL_PAGE ; 
 int /*<<< orphan*/  VSC8501_RGMII_CTRL_REG ; 
 int VSC8501_RGMII_DELAY_MASK ; 
 int VSC8501_RGMII_DELAY_RXSHIFT ; 
 int VSC8501_RGMII_DELAY_TXSHIFT ; 
 int VSC8501_RGMII_LANESWAP ; 
 int VSC8501_RGMII_RXCLOCK_DISABLE ; 
 int vscphy_read (struct vscphy_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vscphy_write (struct vscphy_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vsc8501_setup_rgmii(struct vscphy_softc *vsc)
{
	int reg;

	vscphy_write(vsc, VSC8501_EXTPAGE_REG, VSC8501_RGMII_CTRL_PAGE);

	reg = vscphy_read(vsc, VSC8501_RGMII_CTRL_REG);
	reg &= ~VSC8501_RGMII_RXCLOCK_DISABLE;
	reg &= ~VSC8501_RGMII_LANESWAP;
	reg &= ~(VSC8501_RGMII_DELAY_MASK << VSC8501_RGMII_DELAY_TXSHIFT);
	reg &= ~(VSC8501_RGMII_DELAY_MASK << VSC8501_RGMII_DELAY_RXSHIFT);
	if (vsc->laneswap)
		reg |= VSC8501_RGMII_LANESWAP;
	if (vsc->contype == MII_CONTYPE_RGMII_ID || 
	    vsc->contype == MII_CONTYPE_RGMII_TXID) {
		reg |= vsc->txdelay << VSC8501_RGMII_DELAY_TXSHIFT;
	}
	if (vsc->contype == MII_CONTYPE_RGMII_ID || 
	    vsc->contype == MII_CONTYPE_RGMII_RXID) {
		reg |= vsc->rxdelay << VSC8501_RGMII_DELAY_RXSHIFT;
	}
	vscphy_write(vsc, VSC8501_RGMII_CTRL_REG, reg);

	vscphy_write(vsc, VSC8501_EXTPAGE_REG, 0);
}