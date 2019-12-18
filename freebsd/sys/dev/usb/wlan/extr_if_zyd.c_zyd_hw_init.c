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
struct zyd_rf {int (* init ) (struct zyd_rf*) ;} ;
struct zyd_softc {int sc_fwbase; int sc_fwrev; scalar_t__ sc_macrev; scalar_t__ sc_fix_cr157; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_rfrev; struct zyd_rf sc_rf; } ;
struct zyd_phy_pair {scalar_t__ reg; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct zyd_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ZYD_CR157 ; 
 int /*<<< orphan*/  ZYD_CR_ADDA_MBIAS_WT ; 
 int /*<<< orphan*/  ZYD_CR_ADDA_PWR_DWN ; 
 int /*<<< orphan*/  ZYD_CR_GPI_EN ; 
 int /*<<< orphan*/  ZYD_CR_INTERRUPT ; 
 int /*<<< orphan*/  ZYD_CR_PS_CTRL ; 
 int /*<<< orphan*/  ZYD_CR_RX_PE_DELAY ; 
 int /*<<< orphan*/  ZYD_DEBUG_FW ; 
 int ZYD_EEPROM_PHY_REG ; 
 int ZYD_FIRMWARE_BASE_ADDR ; 
 int ZYD_FW_FIRMWARE_REV ; 
 int /*<<< orphan*/  ZYD_MACB_AIFS_CTL1 ; 
 int /*<<< orphan*/  ZYD_MACB_AIFS_CTL2 ; 
 int /*<<< orphan*/  ZYD_MACB_MAX_RETRY ; 
 int /*<<< orphan*/  ZYD_MACB_TXOP ; 
 int /*<<< orphan*/  ZYD_MACB_TXPWR_CTL1 ; 
 int /*<<< orphan*/  ZYD_MACB_TXPWR_CTL2 ; 
 int /*<<< orphan*/  ZYD_MACB_TXPWR_CTL3 ; 
 int /*<<< orphan*/  ZYD_MACB_TXPWR_CTL4 ; 
 int /*<<< orphan*/  ZYD_MAC_ACK_EXT ; 
 int /*<<< orphan*/  ZYD_MAC_AFTER_PNP ; 
 int /*<<< orphan*/  ZYD_MAC_BACKOFF_PROTECT ; 
 int /*<<< orphan*/  ZYD_MAC_BCNCFG ; 
 int /*<<< orphan*/  ZYD_MAC_CAM_MODE ; 
 int /*<<< orphan*/  ZYD_MAC_CONT_WIN_LIMIT ; 
 int /*<<< orphan*/  ZYD_MAC_DIFS_EIFS_SIFS ; 
 int /*<<< orphan*/  ZYD_MAC_GHTBH ; 
 int /*<<< orphan*/  ZYD_MAC_GHTBL ; 
 int /*<<< orphan*/  ZYD_MAC_MAN_RATE ; 
 int /*<<< orphan*/  ZYD_MAC_MISC ; 
 int /*<<< orphan*/  ZYD_MAC_PHY_DELAY2 ; 
 int /*<<< orphan*/  ZYD_MAC_RETRY ; 
 int /*<<< orphan*/  ZYD_MAC_RTSCTSRATE ; 
 int /*<<< orphan*/  ZYD_MAC_RXFILTER ; 
 int /*<<< orphan*/  ZYD_MAC_RX_THRESHOLD ; 
 int /*<<< orphan*/  ZYD_MAC_SIFS_ACK_TIME ; 
 int /*<<< orphan*/  ZYD_MAC_SNIFFER ; 
 scalar_t__ ZYD_ZD1211 ; 
 scalar_t__ ZYD_ZD1211B ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int stub1 (struct zyd_rf*) ; 
 struct zyd_phy_pair* zyd_def_phy ; 
 struct zyd_phy_pair* zyd_def_phyB ; 
 int zyd_lock_phy (struct zyd_softc*) ; 
 int /*<<< orphan*/  zyd_read16_m (struct zyd_softc*,int,int*) ; 
 int zyd_read_eeprom (struct zyd_softc*) ; 
 int zyd_read_pod (struct zyd_softc*) ; 
 int zyd_rf_attach (struct zyd_softc*,int /*<<< orphan*/ ) ; 
 int zyd_set_beacon_interval (struct zyd_softc*,int) ; 
 int zyd_unlock_phy (struct zyd_softc*) ; 
 int /*<<< orphan*/  zyd_write16_m (struct zyd_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zyd_write32_m (struct zyd_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
zyd_hw_init(struct zyd_softc *sc)
{
	int error;
	const struct zyd_phy_pair *phyp;
	struct zyd_rf *rf = &sc->sc_rf;
	uint16_t val;

	/* specify that the plug and play is finished */
	zyd_write32_m(sc, ZYD_MAC_AFTER_PNP, 1);
	zyd_read16_m(sc, ZYD_FIRMWARE_BASE_ADDR, &sc->sc_fwbase);
	DPRINTF(sc, ZYD_DEBUG_FW, "firmware base address=0x%04x\n",
	    sc->sc_fwbase);

	/* retrieve firmware revision number */
	zyd_read16_m(sc, sc->sc_fwbase + ZYD_FW_FIRMWARE_REV, &sc->sc_fwrev);
	zyd_write32_m(sc, ZYD_CR_GPI_EN, 0);
	zyd_write32_m(sc, ZYD_MAC_CONT_WIN_LIMIT, 0x7f043f);
	/* set mandatory rates - XXX assumes 802.11b/g */
	zyd_write32_m(sc, ZYD_MAC_MAN_RATE, 0x150f);

	/* disable interrupts */
	zyd_write32_m(sc, ZYD_CR_INTERRUPT, 0);

	if ((error = zyd_read_pod(sc)) != 0) {
		device_printf(sc->sc_dev, "could not read EEPROM\n");
		goto fail;
	}

	/* PHY init (resetting) */
	error = zyd_lock_phy(sc);
	if (error != 0)
		goto fail;
	phyp = (sc->sc_macrev == ZYD_ZD1211B) ? zyd_def_phyB : zyd_def_phy;
	for (; phyp->reg != 0; phyp++)
		zyd_write16_m(sc, phyp->reg, phyp->val);
	if (sc->sc_macrev == ZYD_ZD1211 && sc->sc_fix_cr157 != 0) {
		zyd_read16_m(sc, ZYD_EEPROM_PHY_REG, &val);
		zyd_write32_m(sc, ZYD_CR157, val >> 8);
	}
	error = zyd_unlock_phy(sc);
	if (error != 0)
		goto fail;

	/* HMAC init */
	zyd_write32_m(sc, ZYD_MAC_ACK_EXT, 0x00000020);
	zyd_write32_m(sc, ZYD_CR_ADDA_MBIAS_WT, 0x30000808);
	zyd_write32_m(sc, ZYD_MAC_SNIFFER, 0x00000000);
	zyd_write32_m(sc, ZYD_MAC_RXFILTER, 0x00000000);
	zyd_write32_m(sc, ZYD_MAC_GHTBL, 0x00000000);
	zyd_write32_m(sc, ZYD_MAC_GHTBH, 0x80000000);
	zyd_write32_m(sc, ZYD_MAC_MISC, 0x000000a4);
	zyd_write32_m(sc, ZYD_CR_ADDA_PWR_DWN, 0x0000007f);
	zyd_write32_m(sc, ZYD_MAC_BCNCFG, 0x00f00401);
	zyd_write32_m(sc, ZYD_MAC_PHY_DELAY2, 0x00000000);
	zyd_write32_m(sc, ZYD_MAC_ACK_EXT, 0x00000080);
	zyd_write32_m(sc, ZYD_CR_ADDA_PWR_DWN, 0x00000000);
	zyd_write32_m(sc, ZYD_MAC_SIFS_ACK_TIME, 0x00000100);
	zyd_write32_m(sc, ZYD_CR_RX_PE_DELAY, 0x00000070);
	zyd_write32_m(sc, ZYD_CR_PS_CTRL, 0x10000000);
	zyd_write32_m(sc, ZYD_MAC_RTSCTSRATE, 0x02030203);
	zyd_write32_m(sc, ZYD_MAC_AFTER_PNP, 1);
	zyd_write32_m(sc, ZYD_MAC_BACKOFF_PROTECT, 0x00000114);
	zyd_write32_m(sc, ZYD_MAC_DIFS_EIFS_SIFS, 0x0a47c032);
	zyd_write32_m(sc, ZYD_MAC_CAM_MODE, 0x3);

	if (sc->sc_macrev == ZYD_ZD1211) {
		zyd_write32_m(sc, ZYD_MAC_RETRY, 0x00000002);
		zyd_write32_m(sc, ZYD_MAC_RX_THRESHOLD, 0x000c0640);
	} else {
		zyd_write32_m(sc, ZYD_MACB_MAX_RETRY, 0x02020202);
		zyd_write32_m(sc, ZYD_MACB_TXPWR_CTL4, 0x007f003f);
		zyd_write32_m(sc, ZYD_MACB_TXPWR_CTL3, 0x007f003f);
		zyd_write32_m(sc, ZYD_MACB_TXPWR_CTL2, 0x003f001f);
		zyd_write32_m(sc, ZYD_MACB_TXPWR_CTL1, 0x001f000f);
		zyd_write32_m(sc, ZYD_MACB_AIFS_CTL1, 0x00280028);
		zyd_write32_m(sc, ZYD_MACB_AIFS_CTL2, 0x008C003C);
		zyd_write32_m(sc, ZYD_MACB_TXOP, 0x01800824);
		zyd_write32_m(sc, ZYD_MAC_RX_THRESHOLD, 0x000c0eff);
	}

	/* init beacon interval to 100ms */
	if ((error = zyd_set_beacon_interval(sc, 100)) != 0)
		goto fail;

	if ((error = zyd_rf_attach(sc, sc->sc_rfrev)) != 0) {
		device_printf(sc->sc_dev, "could not attach RF, rev 0x%x\n",
		    sc->sc_rfrev);
		goto fail;
	}

	/* RF chip init */
	error = zyd_lock_phy(sc);
	if (error != 0)
		goto fail;
	error = (*rf->init)(rf);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "radio initialization failed, error %d\n", error);
		goto fail;
	}
	error = zyd_unlock_phy(sc);
	if (error != 0)
		goto fail;

	if ((error = zyd_read_eeprom(sc)) != 0) {
		device_printf(sc->sc_dev, "could not read EEPROM\n");
		goto fail;
	}

fail:	return (error);
}