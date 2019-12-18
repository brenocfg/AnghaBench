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
typedef  int uint16_t ;
typedef  int u_int ;
struct bwi_softc {scalar_t__ sc_pci_subvid; scalar_t__ sc_pci_subdid; } ;
struct bwi_rf {scalar_t__ rf_type; int rf_curchan; } ;
struct bwi_phy {int phy_version; int phy_flags; int phy_rev; } ;
struct bwi_mac {struct bwi_phy mac_phy; struct bwi_rf mac_rf; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_BPHY_CTRL ; 
 int /*<<< orphan*/  BWI_BPHY_CTRL_INIT ; 
 scalar_t__ BWI_PCI_SUBDEVICE_BU4306 ; 
 int BWI_PHY_F_LINKED ; 
 int /*<<< orphan*/  BWI_PHY_MAGIC_REG1 ; 
 int /*<<< orphan*/  BWI_PHY_MAGIC_REG1_VAL1 ; 
 int /*<<< orphan*/  BWI_RF_ANTDIV ; 
 scalar_t__ BWI_RF_T_BCM2050 ; 
 int /*<<< orphan*/  CSR_FILT_SETBITS_2 (struct bwi_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_VENDOR_BROADCOM ; 
 int /*<<< orphan*/  PHY_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int /*<<< orphan*/  PHY_SETBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  RF_SETBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  RF_WRITE (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  bwi_mac_set_tpctl_11bg (struct bwi_mac*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwi_rf_set_chan (struct bwi_mac*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_phy_init_11b_rev5(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_rf *rf = &mac->mac_rf;
	struct bwi_phy *phy = &mac->mac_phy;
	u_int orig_chan;

	if (phy->phy_version == 1)
		RF_SETBITS(mac, 0x7a, 0x50);

	if (sc->sc_pci_subvid != PCI_VENDOR_BROADCOM &&
	    sc->sc_pci_subdid != BWI_PCI_SUBDEVICE_BU4306) {
		uint16_t ofs, val;

		val = 0x2120;
		for (ofs = 0xa8; ofs < 0xc7; ++ofs) {
			PHY_WRITE(mac, ofs, val);
			val += 0x202;
		}
	}

	PHY_FILT_SETBITS(mac, 0x35, 0xf0ff, 0x700);

	if (rf->rf_type == BWI_RF_T_BCM2050)
		PHY_WRITE(mac, 0x38, 0x667);

	if ((phy->phy_flags & BWI_PHY_F_LINKED) || phy->phy_rev >= 2) {
		if (rf->rf_type == BWI_RF_T_BCM2050) {
			RF_SETBITS(mac, 0x7a, 0x20);
			RF_SETBITS(mac, 0x51, 0x4);
		}

		CSR_WRITE_2(sc, BWI_RF_ANTDIV, 0);

		PHY_SETBITS(mac, 0x802, 0x100);
		PHY_SETBITS(mac, 0x42b, 0x2000);
		PHY_WRITE(mac, 0x1c, 0x186a);

		PHY_FILT_SETBITS(mac, 0x13, 0xff, 0x1900);
		PHY_FILT_SETBITS(mac, 0x35, 0xffc0, 0x64);
		PHY_FILT_SETBITS(mac, 0x5d, 0xff80, 0xa);
	}

	/* TODO: bad_frame_preempt? */

	if (phy->phy_version == 1) {
	    	PHY_WRITE(mac, 0x26, 0xce00);
		PHY_WRITE(mac, 0x21, 0x3763);
		PHY_WRITE(mac, 0x22, 0x1bc3);
		PHY_WRITE(mac, 0x23, 0x6f9);
		PHY_WRITE(mac, 0x24, 0x37e);
	} else {
		PHY_WRITE(mac, 0x26, 0xcc00);
	}
	PHY_WRITE(mac, 0x30, 0xc6);

	CSR_WRITE_2(sc, BWI_BPHY_CTRL, BWI_BPHY_CTRL_INIT);

	if (phy->phy_version == 1)
		PHY_WRITE(mac, 0x20, 0x3e1c);
	else
		PHY_WRITE(mac, 0x20, 0x301c);

	if (phy->phy_version == 0)
		CSR_WRITE_2(sc, BWI_PHY_MAGIC_REG1, BWI_PHY_MAGIC_REG1_VAL1);

	/* Force to channel 7 */
	orig_chan = rf->rf_curchan;
	bwi_rf_set_chan(mac, 7, 0);

	if (rf->rf_type != BWI_RF_T_BCM2050) {
		RF_WRITE(mac, 0x75, 0x80);
		RF_WRITE(mac, 0x79, 0x81);
	}

	RF_WRITE(mac, 0x50, 0x20);
	RF_WRITE(mac, 0x50, 0x23);

	if (rf->rf_type == BWI_RF_T_BCM2050) {
		RF_WRITE(mac, 0x50, 0x20);
		RF_WRITE(mac, 0x5a, 0x70);
	}

	RF_WRITE(mac, 0x5b, 0x7b);
	RF_WRITE(mac, 0x5c, 0xb0);
	RF_SETBITS(mac, 0x7a, 0x7);

	bwi_rf_set_chan(mac, orig_chan, 0);

	PHY_WRITE(mac, 0x14, 0x80);
	PHY_WRITE(mac, 0x32, 0xca);
	PHY_WRITE(mac, 0x2a, 0x88a3);

	bwi_mac_set_tpctl_11bg(mac, NULL);

	if (rf->rf_type == BWI_RF_T_BCM2050)
		RF_WRITE(mac, 0x5d, 0xd);

	CSR_FILT_SETBITS_2(sc, BWI_PHY_MAGIC_REG1, 0xffc0, 0x4);
}