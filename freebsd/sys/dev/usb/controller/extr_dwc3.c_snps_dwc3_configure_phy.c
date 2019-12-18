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
struct snps_dwc3_softc {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GUSB2PHYCFG0 ; 
 int DWC3_GUSB2PHYCFG0_PHYIF ; 
 int DWC3_GUSB2PHYCFG0_USBTRDTIM (int) ; 
 int DWC3_GUSB2PHYCFG0_USBTRDTIM_16BITS ; 
 int DWC3_GUSB2PHYCFG0_USBTRDTIM_8BITS ; 
 int DWC3_READ (struct snps_dwc3_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_WRITE (struct snps_dwc3_softc*,int /*<<< orphan*/ ,int) ; 
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
snps_dwc3_configure_phy(struct snps_dwc3_softc *sc)
{
	char *phy_type;
	uint32_t reg;
	int nphy_types;

	phy_type = NULL;
	nphy_types = OF_getprop_alloc(sc->node, "phy_type", (void **)&phy_type);
	if (nphy_types <= 0)
		return;

	reg = DWC3_READ(sc, DWC3_GUSB2PHYCFG0);
	if (strncmp(phy_type, "utmi_wide", 9) == 0) {
		reg &= ~(DWC3_GUSB2PHYCFG0_PHYIF | DWC3_GUSB2PHYCFG0_USBTRDTIM(0xf));
		reg |= DWC3_GUSB2PHYCFG0_PHYIF |
			DWC3_GUSB2PHYCFG0_USBTRDTIM(DWC3_GUSB2PHYCFG0_USBTRDTIM_16BITS);
	} else {
		reg &= ~(DWC3_GUSB2PHYCFG0_PHYIF | DWC3_GUSB2PHYCFG0_USBTRDTIM(0xf));
		reg |= DWC3_GUSB2PHYCFG0_PHYIF |
			DWC3_GUSB2PHYCFG0_USBTRDTIM(DWC3_GUSB2PHYCFG0_USBTRDTIM_8BITS);
	}
	DWC3_WRITE(sc, DWC3_GUSB2PHYCFG0, reg);
}