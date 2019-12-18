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
typedef  int uint8_t ;
struct urtw_softc {scalar_t__ (* sc_rf_stop ) (struct urtw_softc*) ;int /*<<< orphan*/  sc_watchdog_ch; int /*<<< orphan*/  sc_led_ch; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_ASSERT_LOCKED (struct urtw_softc*) ; 
 int /*<<< orphan*/  URTW_CMD ; 
 int URTW_CMD_RX_ENABLE ; 
 int URTW_CMD_TX_ENABLE ; 
 int /*<<< orphan*/  URTW_CONFIG4 ; 
 int URTW_CONFIG4_VCOOFF ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  URTW_RUNNING ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_abort_xfers (struct urtw_softc*) ; 
 scalar_t__ urtw_intr_disable (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ urtw_set_mode (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 

__attribute__((used)) static void
urtw_stop(struct urtw_softc *sc)
{
	uint8_t data8;
	usb_error_t error;

	URTW_ASSERT_LOCKED(sc);

	sc->sc_flags &= ~URTW_RUNNING;

	error = urtw_intr_disable(sc);
	if (error)
		goto fail;
	urtw_read8_m(sc, URTW_CMD, &data8);
	data8 &= ~(URTW_CMD_RX_ENABLE | URTW_CMD_TX_ENABLE);
	urtw_write8_m(sc, URTW_CMD, data8);

	error = sc->sc_rf_stop(sc);
	if (error != 0)
		goto fail;

	error = urtw_set_mode(sc, URTW_EPROM_CMD_CONFIG);
	if (error)
		goto fail;
	urtw_read8_m(sc, URTW_CONFIG4, &data8);
	urtw_write8_m(sc, URTW_CONFIG4, data8 | URTW_CONFIG4_VCOOFF);
	error = urtw_set_mode(sc, URTW_EPROM_CMD_NORMAL);
	if (error)
		goto fail;
fail:
	if (error)
		device_printf(sc->sc_dev, "failed to stop (%s)\n",
		    usbd_errstr(error));

	usb_callout_stop(&sc->sc_led_ch);
	callout_stop(&sc->sc_watchdog_ch);

	urtw_abort_xfers(sc);
}