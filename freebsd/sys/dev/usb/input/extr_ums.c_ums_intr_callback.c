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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
typedef  unsigned long uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fp; } ;
struct TYPE_3__ {unsigned long button; unsigned long dx; unsigned long dy; unsigned long dz; } ;
struct ums_softc {int* sc_temp; int /*<<< orphan*/  sc_evflags; TYPE_2__ sc_fifo; int /*<<< orphan*/  sc_callout; struct ums_info* sc_info; TYPE_1__ sc_status; int /*<<< orphan*/  sc_iid; } ;
struct ums_info {int sc_flags; int sc_iid_w; int sc_iid_x; int sc_iid_y; int sc_iid_z; int sc_iid_t; int sc_buttons; int* sc_iid_btn; int /*<<< orphan*/ * sc_loc_btn; int /*<<< orphan*/  sc_loc_t; int /*<<< orphan*/  sc_loc_z; int /*<<< orphan*/  sc_loc_y; int /*<<< orphan*/  sc_loc_x; int /*<<< orphan*/  sc_loc_w; } ;
typedef  unsigned long int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 unsigned long UMS_BUT (int) ; 
 int UMS_FLAG_REVZ ; 
 int UMS_FLAG_SBU ; 
 int UMS_FLAG_T_AXIS ; 
 int UMS_FLAG_W_AXIS ; 
 int UMS_FLAG_X_AXIS ; 
 int UMS_FLAG_Y_AXIS ; 
 int UMS_FLAG_Z_AXIS ; 
 size_t UMS_INFO_MAX ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 size_t USB_FIFO_RX ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 unsigned long hid_get_data (int*,int,int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  ums_evdev_push (struct ums_softc*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ums_put_queue (struct ums_softc*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ums_put_queue_timeout ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct ums_softc*) ; 
 int /*<<< orphan*/  usb_callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fifo_put_bytes_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ums_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ums_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ums_softc *sc = usbd_xfer_softc(xfer);
	struct ums_info *info = &sc->sc_info[0];
	struct usb_page_cache *pc;
	uint8_t *buf = sc->sc_temp;
	int32_t buttons = 0;
	int32_t buttons_found = 0;
#ifdef EVDEV_SUPPORT
	int32_t buttons_reported = 0;
#endif
	int32_t dw = 0;
	int32_t dx = 0;
	int32_t dy = 0;
	int32_t dz = 0;
	int32_t dt = 0;
	uint8_t i;
	uint8_t id;
	int len;

	usbd_xfer_status(xfer, &len, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTFN(6, "sc=%p actlen=%d\n", sc, len);

		if (len > (int)sizeof(sc->sc_temp)) {
			DPRINTFN(6, "truncating large packet to %zu bytes\n",
			    sizeof(sc->sc_temp));
			len = sizeof(sc->sc_temp);
		}
		if (len == 0)
			goto tr_setup;

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, buf, len);

		DPRINTFN(6, "data = %02x %02x %02x %02x "
		    "%02x %02x %02x %02x\n",
		    (len > 0) ? buf[0] : 0, (len > 1) ? buf[1] : 0,
		    (len > 2) ? buf[2] : 0, (len > 3) ? buf[3] : 0,
		    (len > 4) ? buf[4] : 0, (len > 5) ? buf[5] : 0,
		    (len > 6) ? buf[6] : 0, (len > 7) ? buf[7] : 0);

		if (sc->sc_iid) {
			id = *buf;

			len--;
			buf++;

		} else {
			id = 0;
			if (sc->sc_info[0].sc_flags & UMS_FLAG_SBU) {
				if ((*buf == 0x14) || (*buf == 0x15)) {
					goto tr_setup;
				}
			}
		}

	repeat:
		if ((info->sc_flags & UMS_FLAG_W_AXIS) &&
		    (id == info->sc_iid_w))
			dw += hid_get_data(buf, len, &info->sc_loc_w);

		if ((info->sc_flags & UMS_FLAG_X_AXIS) && 
		    (id == info->sc_iid_x))
			dx += hid_get_data(buf, len, &info->sc_loc_x);

		if ((info->sc_flags & UMS_FLAG_Y_AXIS) &&
		    (id == info->sc_iid_y))
			dy -= hid_get_data(buf, len, &info->sc_loc_y);

		if ((info->sc_flags & UMS_FLAG_Z_AXIS) &&
		    (id == info->sc_iid_z)) {
			int32_t temp;
			temp = hid_get_data(buf, len, &info->sc_loc_z);
			if (info->sc_flags & UMS_FLAG_REVZ)
				temp = -temp;
			dz -= temp;
		}

		if ((info->sc_flags & UMS_FLAG_T_AXIS) &&
		    (id == info->sc_iid_t)) {
			dt += hid_get_data(buf, len, &info->sc_loc_t);
			/* T-axis is translated into button presses */
			buttons_found |= (1UL << 5) | (1UL << 6);
		}

		for (i = 0; i < info->sc_buttons; i++) {
			uint32_t mask;
			mask = 1UL << UMS_BUT(i);
			/* check for correct button ID */
			if (id != info->sc_iid_btn[i])
				continue;
			/* check for button pressed */
			if (hid_get_data(buf, len, &info->sc_loc_btn[i]))
				buttons |= mask;
			/* register button mask */
			buttons_found |= mask;
		}

		if (++info != &sc->sc_info[UMS_INFO_MAX])
			goto repeat;

#ifdef EVDEV_SUPPORT
		buttons_reported = buttons;
#endif
		/* keep old button value(s) for non-detected buttons */
		buttons |= sc->sc_status.button & ~buttons_found;

		if (dx || dy || dz || dt || dw ||
		    (buttons != sc->sc_status.button)) {

			DPRINTFN(6, "x:%d y:%d z:%d t:%d w:%d buttons:0x%08x\n",
			    dx, dy, dz, dt, dw, buttons);

			/* translate T-axis into button presses until further */
			if (dt > 0) {
				ums_put_queue(sc, 0, 0, 0, 0, buttons);
				buttons |= 1UL << 6;
			} else if (dt < 0) {
				ums_put_queue(sc, 0, 0, 0, 0, buttons);
				buttons |= 1UL << 5;
			}

			sc->sc_status.button = buttons;
			sc->sc_status.dx += dx;
			sc->sc_status.dy += dy;
			sc->sc_status.dz += dz;
			/*
			 * sc->sc_status.dt += dt;
			 * no way to export this yet
			 */

			/*
		         * The Qtronix keyboard has a built in PS/2
		         * port for a mouse.  The firmware once in a
		         * while posts a spurious button up
		         * event. This event we ignore by doing a
		         * timeout for 50 msecs.  If we receive
		         * dx=dy=dz=buttons=0 before we add the event
		         * to the queue.  In any other case we delete
		         * the timeout event.
		         */
			if ((sc->sc_info[0].sc_flags & UMS_FLAG_SBU) &&
			    (dx == 0) && (dy == 0) && (dz == 0) && (dt == 0) &&
			    (dw == 0) && (buttons == 0)) {

				usb_callout_reset(&sc->sc_callout, hz / 20,
				    &ums_put_queue_timeout, sc);
			} else {

				usb_callout_stop(&sc->sc_callout);

				ums_put_queue(sc, dx, dy, dz, dt, buttons);
#ifdef EVDEV_SUPPORT
				ums_evdev_push(sc, dx, dy, dz, dt,
				    buttons_reported);
#endif

			}
		}
	case USB_ST_SETUP:
tr_setup:
		/* check if we can put more data into the FIFO */
		if (usb_fifo_put_bytes_max(sc->sc_fifo.fp[USB_FIFO_RX]) == 0) {
#ifdef EVDEV_SUPPORT
			if (sc->sc_evflags == 0)
				break;
#else
			break;
#endif
		}

		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* try clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}