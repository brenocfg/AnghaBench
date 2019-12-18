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
struct vscphy_softc {int /*<<< orphan*/  contype; int /*<<< orphan*/  mii_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VSC8501_EXTCTL1_REG ; 
 int VSC8501_EXTCTL1_RGMII_MODE ; 
 scalar_t__ mii_contype_is_rgmii (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_phy_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsc8501_setup_rgmii (struct vscphy_softc*) ; 
 int vscphy_read (struct vscphy_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vscphy_write (struct vscphy_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vsc8501_reset(struct vscphy_softc *vsc)
{
	int reg;

	/*
	 * Must set whether the mac<->phy connection is RGMII first; changes to
	 * that bit take effect only after a softreset.
	 */
	reg = vscphy_read(vsc, VSC8501_EXTCTL1_REG);
	if (mii_contype_is_rgmii(vsc->contype))
		reg |= VSC8501_EXTCTL1_RGMII_MODE;
	else
		reg &= ~VSC8501_EXTCTL1_RGMII_MODE;
	vscphy_write(vsc, VSC8501_EXTCTL1_REG, reg);

	mii_phy_reset(&vsc->mii_sc);

	/*
	 * Setup rgmii control register if necessary, after softreset.
	 */
	if (mii_contype_is_rgmii(vsc->contype))
	    vsc8501_setup_rgmii(vsc);
}