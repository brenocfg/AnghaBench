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
typedef  int u_long ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
struct TYPE_4__ {int level; int packetsize; } ;
struct adb_mouse_softc {int buttons; int last_buttons; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  ydelta; int /*<<< orphan*/  xdelta; TYPE_2__ mode; int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {int button; int obutton; int flags; int /*<<< orphan*/  dz; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
typedef  TYPE_1__ mousestatus_t ;
typedef  TYPE_2__ mousemode_t ;
typedef  int /*<<< orphan*/  mousehw_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 struct adb_mouse_softc* CDEV_GET_SOFTC (struct cdev*) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOTTY ; 
 int MOUSE_BUTTONSCHANGED ; 
#define  MOUSE_GETHWINFO 133 
#define  MOUSE_GETLEVEL 132 
#define  MOUSE_GETMODE 131 
#define  MOUSE_GETSTATUS 130 
 int MOUSE_POSCHANGED ; 
#define  MOUSE_SETLEVEL 129 
#define  MOUSE_SETMODE 128 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ams_ioctl(struct cdev *dev, u_long cmd, caddr_t addr, int flag, 
    struct thread *p)
{
	struct adb_mouse_softc *sc;
	mousemode_t mode;

	sc = CDEV_GET_SOFTC(dev);
	if (sc == NULL)
		return (EIO);

	switch (cmd) {
	case MOUSE_GETHWINFO:
		*(mousehw_t *)addr = sc->hw;
		break;
	case MOUSE_GETMODE:
		*(mousemode_t *)addr = sc->mode;
		break;
	case MOUSE_SETMODE:
		mode = *(mousemode_t *)addr;
		addr = (caddr_t)&mode.level;

		/* Fallthrough */

	case MOUSE_SETLEVEL:
		if (*(int *)addr == -1)
			break;
		else if (*(int *)addr == 1) {
			sc->mode.level = 1;
			sc->mode.packetsize = 8;
			break;
		} else if (*(int *)addr == 0) {
			sc->mode.level = 0;
			sc->mode.packetsize = 5;
			break;
		}
	
		return EINVAL;
	case MOUSE_GETLEVEL:
		*(int *)addr = sc->mode.level;
		break;
	
	case MOUSE_GETSTATUS: {
		mousestatus_t *status = (mousestatus_t *) addr;

		mtx_lock(&sc->sc_mtx);

		status->button = sc->buttons;
		status->obutton = sc->last_buttons;
		
		status->flags = status->button ^ status->obutton;

		if (sc->xdelta != 0 || sc->ydelta)
			status->flags |= MOUSE_POSCHANGED;
		if (status->button != status->obutton)
			status->flags |= MOUSE_BUTTONSCHANGED;

		status->dx = sc->xdelta;
		status->dy = sc->ydelta;
		status->dz = 0;

		sc->xdelta = 0;
		sc->ydelta = 0;
		sc->last_buttons = sc->buttons;

		mtx_unlock(&sc->sc_mtx);

		break; }
	default:
		return ENOTTY;
	}

	return (0);
}