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
typedef  scalar_t__ usb_error_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211com {int /*<<< orphan*/ * ic_macaddr; int /*<<< orphan*/  ic_vaps; } ;
struct urtw_softc {scalar_t__ (* sc_rf_init ) (struct urtw_softc*) ;int /*<<< orphan*/  sc_sens; int /*<<< orphan*/  (* sc_rf_set_sens ) (struct urtw_softc*,int /*<<< orphan*/ ) ;struct ieee80211com sc_ic; } ;
struct ieee80211vap {int /*<<< orphan*/ * iv_myaddr; } ;

/* Variables and functions */
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  URTW_ADDR_MAGIC1 ; 
 int /*<<< orphan*/  URTW_ADDR_MAGIC2 ; 
 int /*<<< orphan*/  URTW_ADDR_MAGIC3 ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  URTW_GPIO ; 
 int /*<<< orphan*/  URTW_INT_TIMEOUT ; 
 int /*<<< orphan*/  URTW_LED_CTL_POWER_ON ; 
 int /*<<< orphan*/  URTW_PSR ; 
 int /*<<< orphan*/  URTW_RATE_FALLBACK ; 
 int URTW_RATE_FALLBACK_ENABLE ; 
 int /*<<< orphan*/  URTW_TALLY_SEL ; 
 int /*<<< orphan*/  URTW_WPA_CONFIG ; 
 scalar_t__ stub1 (struct urtw_softc*) ; 
 int /*<<< orphan*/  stub2 (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ urtw_intr_enable (struct urtw_softc*) ; 
 scalar_t__ urtw_led_ctl (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ urtw_reset (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_set_macaddr (struct urtw_softc*,int /*<<< orphan*/  const*) ; 
 scalar_t__ urtw_set_mode (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ urtw_set_rate (struct urtw_softc*) ; 
 scalar_t__ urtw_update_msr (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_write16_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  urtw_write32_m (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static usb_error_t
urtw_adapter_start(struct urtw_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	const uint8_t *macaddr;
	usb_error_t error;

	error = urtw_reset(sc);
	if (error)
		goto fail;

	urtw_write8_m(sc, URTW_ADDR_MAGIC1, 0);
	urtw_write8_m(sc, URTW_GPIO, 0);

	/* for led  */
	urtw_write8_m(sc, URTW_ADDR_MAGIC1, 4);
	error = urtw_led_ctl(sc, URTW_LED_CTL_POWER_ON);
	if (error != 0)
		goto fail;

	error = urtw_set_mode(sc, URTW_EPROM_CMD_CONFIG);
	if (error)
		goto fail;
	/* applying MAC address again.  */
	macaddr = vap ? vap->iv_myaddr : ic->ic_macaddr;
	urtw_set_macaddr(sc, macaddr);
	if (error)
		goto fail;

	error = urtw_set_mode(sc, URTW_EPROM_CMD_NORMAL);
	if (error)
		goto fail;

	error = urtw_update_msr(sc);
	if (error)
		goto fail;

	urtw_write32_m(sc, URTW_INT_TIMEOUT, 0);
	urtw_write8_m(sc, URTW_WPA_CONFIG, 0);
	urtw_write8_m(sc, URTW_RATE_FALLBACK, URTW_RATE_FALLBACK_ENABLE | 0x1);
	error = urtw_set_rate(sc);
	if (error != 0)
		goto fail;

	error = sc->sc_rf_init(sc);
	if (error != 0)
		goto fail;
	if (sc->sc_rf_set_sens != NULL)
		sc->sc_rf_set_sens(sc, sc->sc_sens);

	/* XXX correct? to call write16  */
	urtw_write16_m(sc, URTW_PSR, 1);
	urtw_write16_m(sc, URTW_ADDR_MAGIC2, 0x10);
	urtw_write8_m(sc, URTW_TALLY_SEL, 0x80);
	urtw_write8_m(sc, URTW_ADDR_MAGIC3, 0x60);
	/* XXX correct? to call write16  */
	urtw_write16_m(sc, URTW_PSR, 0);
	urtw_write8_m(sc, URTW_ADDR_MAGIC1, 4);

	error = urtw_intr_enable(sc);
	if (error != 0)
		goto fail;

fail:
	return (error);
}