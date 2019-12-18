#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int* syncmask; int level; int /*<<< orphan*/  packetsize; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fp; } ;
struct ums_softc {TYPE_2__ sc_mode; TYPE_1__ sc_fifo; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int MOUSE_MSC_BUTTONS ; 
 int MOUSE_SYS_EXTBUTTONS ; 
 size_t USB_FIFO_RX ; 
 int /*<<< orphan*/  usb_fifo_put_data_linear (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ums_put_queue(struct ums_softc *sc, int32_t dx, int32_t dy,
    int32_t dz, int32_t dt, int32_t buttons)
{
	uint8_t buf[8];

	if (1) {

		if (dx > 254)
			dx = 254;
		if (dx < -256)
			dx = -256;
		if (dy > 254)
			dy = 254;
		if (dy < -256)
			dy = -256;
		if (dz > 126)
			dz = 126;
		if (dz < -128)
			dz = -128;
		if (dt > 126)
			dt = 126;
		if (dt < -128)
			dt = -128;

		buf[0] = sc->sc_mode.syncmask[1];
		buf[0] |= (~buttons) & MOUSE_MSC_BUTTONS;
		buf[1] = dx >> 1;
		buf[2] = dy >> 1;
		buf[3] = dx - (dx >> 1);
		buf[4] = dy - (dy >> 1);

		if (sc->sc_mode.level == 1) {
			buf[5] = dz >> 1;
			buf[6] = dz - (dz >> 1);
			buf[7] = (((~buttons) >> 3) & MOUSE_SYS_EXTBUTTONS);
		}
		usb_fifo_put_data_linear(sc->sc_fifo.fp[USB_FIFO_RX], buf,
		    sc->sc_mode.packetsize, 1);
	} else {
		DPRINTF("Buffer full, discarded packet\n");
	}
}