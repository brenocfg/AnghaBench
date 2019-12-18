#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct usb_fifo {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  obutton; int /*<<< orphan*/  button; int /*<<< orphan*/  dz; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
struct TYPE_5__ {int level; void** syncmask; void* packetsize; void* protocol; int /*<<< orphan*/  rate; } ;
struct TYPE_6__ {int buttons; } ;
struct atp_softc {int /*<<< orphan*/  sc_mutex; TYPE_1__ sc_status; TYPE_2__ sc_mode; TYPE_3__ sc_hw; int /*<<< orphan*/  sc_pollrate; } ;
typedef  TYPE_1__ mousestatus_t ;
typedef  TYPE_2__ mousemode_t ;
typedef  TYPE_3__ mousehw_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  MOUSE_BUTTONSCHANGED ; 
#define  MOUSE_GETHWINFO 133 
#define  MOUSE_GETLEVEL 132 
#define  MOUSE_GETMODE 131 
#define  MOUSE_GETSTATUS 130 
 void* MOUSE_MSC_PACKETSIZE ; 
 void* MOUSE_MSC_SYNC ; 
 void* MOUSE_MSC_SYNCMASK ; 
 int /*<<< orphan*/  MOUSE_POSCHANGED ; 
 void* MOUSE_PROTO_MSC ; 
 void* MOUSE_PROTO_SYSMOUSE ; 
#define  MOUSE_SETLEVEL 129 
#define  MOUSE_SETMODE 128 
 void* MOUSE_SYS_PACKETSIZE ; 
 void* MOUSE_SYS_SYNC ; 
 void* MOUSE_SYS_SYNCMASK ; 
 int /*<<< orphan*/  atp_reset_buf (struct atp_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct atp_softc* usb_fifo_softc (struct usb_fifo*) ; 

__attribute__((used)) static int
atp_ioctl(struct usb_fifo *fifo, u_long cmd, void *addr, int fflags)
{
	struct atp_softc *sc = usb_fifo_softc(fifo);
	mousemode_t mode;
	int error = 0;

	mtx_lock(&sc->sc_mutex);

	switch(cmd) {
	case MOUSE_GETHWINFO:
		*(mousehw_t *)addr = sc->sc_hw;
		break;
	case MOUSE_GETMODE:
		*(mousemode_t *)addr = sc->sc_mode;
		break;
	case MOUSE_SETMODE:
		mode = *(mousemode_t *)addr;

		if (mode.level == -1)
			/* Don't change the current setting */
			;
		else if ((mode.level < 0) || (mode.level > 1)) {
			error = EINVAL;
			break;
		}
		sc->sc_mode.level = mode.level;
		sc->sc_pollrate   = mode.rate;
		sc->sc_hw.buttons = 3;

		if (sc->sc_mode.level == 0) {
			sc->sc_mode.protocol    = MOUSE_PROTO_MSC;
			sc->sc_mode.packetsize  = MOUSE_MSC_PACKETSIZE;
			sc->sc_mode.syncmask[0] = MOUSE_MSC_SYNCMASK;
			sc->sc_mode.syncmask[1] = MOUSE_MSC_SYNC;
		} else if (sc->sc_mode.level == 1) {
			sc->sc_mode.protocol    = MOUSE_PROTO_SYSMOUSE;
			sc->sc_mode.packetsize  = MOUSE_SYS_PACKETSIZE;
			sc->sc_mode.syncmask[0] = MOUSE_SYS_SYNCMASK;
			sc->sc_mode.syncmask[1] = MOUSE_SYS_SYNC;
		}
		atp_reset_buf(sc);
		break;
	case MOUSE_GETLEVEL:
		*(int *)addr = sc->sc_mode.level;
		break;
	case MOUSE_SETLEVEL:
		if ((*(int *)addr < 0) || (*(int *)addr > 1)) {
			error = EINVAL;
			break;
		}
		sc->sc_mode.level = *(int *)addr;
		sc->sc_hw.buttons = 3;

		if (sc->sc_mode.level == 0) {
			sc->sc_mode.protocol    = MOUSE_PROTO_MSC;
			sc->sc_mode.packetsize  = MOUSE_MSC_PACKETSIZE;
			sc->sc_mode.syncmask[0] = MOUSE_MSC_SYNCMASK;
			sc->sc_mode.syncmask[1] = MOUSE_MSC_SYNC;
		} else if (sc->sc_mode.level == 1) {
			sc->sc_mode.protocol    = MOUSE_PROTO_SYSMOUSE;
			sc->sc_mode.packetsize  = MOUSE_SYS_PACKETSIZE;
			sc->sc_mode.syncmask[0] = MOUSE_SYS_SYNCMASK;
			sc->sc_mode.syncmask[1] = MOUSE_SYS_SYNC;
		}
		atp_reset_buf(sc);
		break;
	case MOUSE_GETSTATUS: {
		mousestatus_t *status = (mousestatus_t *)addr;

		*status = sc->sc_status;
		sc->sc_status.obutton = sc->sc_status.button;
		sc->sc_status.button  = 0;
		sc->sc_status.dx      = 0;
		sc->sc_status.dy      = 0;
		sc->sc_status.dz      = 0;

		if (status->dx || status->dy || status->dz)
			status->flags |= MOUSE_POSCHANGED;
		if (status->button != status->obutton)
			status->flags |= MOUSE_BUTTONSCHANGED;
		break;
	}

	default:
		error = ENOTTY;
		break;
	}

	mtx_unlock(&sc->sc_mutex);
	return (error);
}