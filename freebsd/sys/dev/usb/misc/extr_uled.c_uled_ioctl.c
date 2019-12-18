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
typedef  char uint8_t ;
typedef  int u_long ;
struct usb_fifo {int dummy; } ;
struct uled_color {char red; char green; char blue; } ;
struct uled_softc {int sc_flags; int /*<<< orphan*/  sc_mtx; struct uled_color sc_color; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENOTTY ; 
 int ULED_FLAG_BLINK1 ; 
#define  ULED_GET_COLOR 129 
#define  ULED_SET_COLOR 128 
 int /*<<< orphan*/  UR_SET_REPORT ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int uled_ctrl_msg (struct uled_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 struct uled_softc* usb_fifo_softc (struct usb_fifo*) ; 

__attribute__((used)) static int
uled_ioctl(struct usb_fifo *fifo, u_long cmd, void *addr, int fflags)
{
	struct uled_softc *sc;
	struct uled_color color;
	int error;

	sc = usb_fifo_softc(fifo);
	error = 0;

	mtx_lock(&sc->sc_mtx);

	switch(cmd) {
	case ULED_GET_COLOR:
		*(struct uled_color *)addr = sc->sc_color;
		break;
	case ULED_SET_COLOR:
		color = *(struct uled_color *)addr;
		uint8_t buf[8];

		sc->sc_color.red = color.red;
		sc->sc_color.green = color.green;
		sc->sc_color.blue = color.blue;

		if (sc->sc_flags & ULED_FLAG_BLINK1) {
			buf[0] = 0x1;
			buf[1] = 'n';
			buf[2] = color.red;
			buf[3] = color.green;
			buf[4] = color.blue;
			buf[5] = buf[6] = buf[7] = 0;
		} else {
			buf[0] = color.red;
			buf[1] = color.green;
			buf[2] = color.blue;
			buf[3] = buf[4] = buf[5] = 0;
			buf[6] = 0x1a;
			buf[7] = 0x05;
		}
		error = uled_ctrl_msg(sc, UT_WRITE_CLASS_INTERFACE,
		    UR_SET_REPORT, 0x200, 0, buf, sizeof(buf));
		break;
	default:
		error = ENOTTY;
		break;
	}

	mtx_unlock(&sc->sc_mtx);
	return (error);
}