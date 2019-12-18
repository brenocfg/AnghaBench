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
struct urtw_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_8225_ANAPARAM2_ON ; 
 int /*<<< orphan*/  URTW_8225_ANAPARAM_ON ; 
 int /*<<< orphan*/  URTW_CMD ; 
 int URTW_CMD_RST ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_LOAD ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ urtw_8180_set_anaparam (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ urtw_8185_set_anaparam2 (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ urtw_intr_disable (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ urtw_set_mode (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ urtw_write8e (struct urtw_softc*,int,int) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urtw_reset(struct urtw_softc *sc)
{
	uint8_t data;
	usb_error_t error;

	error = urtw_8180_set_anaparam(sc, URTW_8225_ANAPARAM_ON);
	if (error)
		goto fail;
	error = urtw_8185_set_anaparam2(sc, URTW_8225_ANAPARAM2_ON);
	if (error)
		goto fail;

	error = urtw_intr_disable(sc);
	if (error)
		goto fail;
	usb_pause_mtx(&sc->sc_mtx, 100);

	error = urtw_write8e(sc, 0x18, 0x10);
	if (error != 0)
		goto fail;
	error = urtw_write8e(sc, 0x18, 0x11);
	if (error != 0)
		goto fail;
	error = urtw_write8e(sc, 0x18, 0x00);
	if (error != 0)
		goto fail;
	usb_pause_mtx(&sc->sc_mtx, 100);

	urtw_read8_m(sc, URTW_CMD, &data);
	data = (data & 0x2) | URTW_CMD_RST;
	urtw_write8_m(sc, URTW_CMD, data);
	usb_pause_mtx(&sc->sc_mtx, 100);

	urtw_read8_m(sc, URTW_CMD, &data);
	if (data & URTW_CMD_RST) {
		device_printf(sc->sc_dev, "reset timeout\n");
		goto fail;
	}

	error = urtw_set_mode(sc, URTW_EPROM_CMD_LOAD);
	if (error)
		goto fail;
	usb_pause_mtx(&sc->sc_mtx, 100);

	error = urtw_8180_set_anaparam(sc, URTW_8225_ANAPARAM_ON);
	if (error)
		goto fail;
	error = urtw_8185_set_anaparam2(sc, URTW_8225_ANAPARAM2_ON);
	if (error)
		goto fail;
fail:
	return (error);
}