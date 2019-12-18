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
struct snps_dwc3_softc {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GUCTL1 ; 
 int /*<<< orphan*/  DWC3_GUCTL1_TX_IPGAP_LINECHECK_DIS ; 
 int /*<<< orphan*/  DWC3_GUSB2PHYCFG0 ; 
 int /*<<< orphan*/  DWC3_GUSB2PHYCFG0_ENBLSLPM ; 
 int /*<<< orphan*/  DWC3_GUSB2PHYCFG0_SUSPENDUSB20 ; 
 int /*<<< orphan*/  DWC3_GUSB2PHYCFG0_U2_FREECLK_EXISTS ; 
 int /*<<< orphan*/  DWC3_GUSB3PIPECTL0 ; 
 int /*<<< orphan*/  DWC3_GUSB3PIPECTL0_DELAYP1TRANS ; 
 int /*<<< orphan*/  DWC3_READ (struct snps_dwc3_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_WRITE (struct snps_dwc3_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
snps_dwc3_do_quirks(struct snps_dwc3_softc *sc)
{
	uint32_t reg;

	reg = DWC3_READ(sc, DWC3_GUSB2PHYCFG0);
	if (OF_hasprop(sc->node, "snps,dis-u2-freeclk-exists-quirk"))
		reg &= ~DWC3_GUSB2PHYCFG0_U2_FREECLK_EXISTS;
	else
		reg |= DWC3_GUSB2PHYCFG0_U2_FREECLK_EXISTS;
	if (OF_hasprop(sc->node, "snps,dis_u2_susphy_quirk"))
		reg &= ~DWC3_GUSB2PHYCFG0_SUSPENDUSB20;
	else
		reg |= DWC3_GUSB2PHYCFG0_SUSPENDUSB20;
	if (OF_hasprop(sc->node, "snps,dis_enblslpm_quirk"))
		reg &= ~DWC3_GUSB2PHYCFG0_ENBLSLPM;
	else
		reg |= DWC3_GUSB2PHYCFG0_ENBLSLPM;

	DWC3_WRITE(sc, DWC3_GUSB2PHYCFG0, reg);

	reg = DWC3_READ(sc, DWC3_GUCTL1);
	if (OF_hasprop(sc->node, "snps,dis-tx-ipgap-linecheck-quirk"))
		reg |= DWC3_GUCTL1_TX_IPGAP_LINECHECK_DIS;
	DWC3_WRITE(sc, DWC3_GUCTL1, reg);

	if (OF_hasprop(sc->node, "snps,dis-del-phy-power-chg-quirk")) {
		reg = DWC3_READ(sc, DWC3_GUSB3PIPECTL0);
		reg |= DWC3_GUSB3PIPECTL0_DELAYP1TRANS;
		DWC3_WRITE(sc, DWC3_GUSB3PIPECTL0, reg);
	}
}