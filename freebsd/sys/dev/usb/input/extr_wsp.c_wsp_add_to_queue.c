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
typedef  int uint32_t ;
struct TYPE_4__ {int* syncmask; int level; int /*<<< orphan*/  packetsize; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fp; } ;
struct wsp_softc {TYPE_2__ sc_mode; TYPE_1__ sc_fifo; } ;

/* Variables and functions */
 int MOUSE_BUTTON1DOWN ; 
 int MOUSE_BUTTON2DOWN ; 
 int MOUSE_BUTTON3DOWN ; 
 int MOUSE_MSC_BUTTON1UP ; 
 int MOUSE_MSC_BUTTON2UP ; 
 int MOUSE_MSC_BUTTON3UP ; 
 int MOUSE_MSC_BUTTONS ; 
 int MOUSE_SYS_EXTBUTTONS ; 
 size_t USB_FIFO_RX ; 
 int imax (int,int) ; 
 int imin (int,int) ; 
 int /*<<< orphan*/  usb_fifo_put_data_linear (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wsp_add_to_queue(struct wsp_softc *sc, int dx, int dy, int dz,
    uint32_t buttons_in)
{
	uint32_t buttons_out;
	uint8_t buf[8];

	dx = imin(dx, 254);
	dx = imax(dx, -256);
	dy = imin(dy, 254);
	dy = imax(dy, -256);
	dz = imin(dz, 126);
	dz = imax(dz, -128);

	buttons_out = MOUSE_MSC_BUTTONS;
	if (buttons_in & MOUSE_BUTTON1DOWN)
		buttons_out &= ~MOUSE_MSC_BUTTON1UP;
	else if (buttons_in & MOUSE_BUTTON2DOWN)
		buttons_out &= ~MOUSE_MSC_BUTTON2UP;
	else if (buttons_in & MOUSE_BUTTON3DOWN)
		buttons_out &= ~MOUSE_MSC_BUTTON3UP;

	/* Encode the mouse data in standard format; refer to mouse(4) */
	buf[0] = sc->sc_mode.syncmask[1];
	buf[0] |= buttons_out;
	buf[1] = dx >> 1;
	buf[2] = dy >> 1;
	buf[3] = dx - (dx >> 1);
	buf[4] = dy - (dy >> 1);
	/* Encode extra bytes for level 1 */
	if (sc->sc_mode.level == 1) {
		buf[5] = dz >> 1;	/* dz / 2 */
		buf[6] = dz - (dz >> 1);/* dz - (dz / 2) */
		buf[7] = (((~buttons_in) >> 3) & MOUSE_SYS_EXTBUTTONS);
	}
	usb_fifo_put_data_linear(sc->sc_fifo.fp[USB_FIFO_RX], buf,
	    sc->sc_mode.packetsize, 1);
}