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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
struct urtw_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_CMD ; 
 int URTW_CMD_RST ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urtw_8187b_cmd_reset(struct urtw_softc *sc)
{
	int i;
	uint8_t data8;
	usb_error_t error;

	/* XXX the code can be duplicate with urtw_reset().  */
	urtw_read8_m(sc, URTW_CMD, &data8);
	data8 = (data8 & 0x2) | URTW_CMD_RST;
	urtw_write8_m(sc, URTW_CMD, data8);

	for (i = 0; i < 20; i++) {
		usb_pause_mtx(&sc->sc_mtx, 2);
		urtw_read8_m(sc, URTW_CMD, &data8);
		if (!(data8 & URTW_CMD_RST))
			break;
	}
	if (i >= 20) {
		device_printf(sc->sc_dev, "reset timeout\n");
		goto fail;
	}
fail:
	return (error);
}