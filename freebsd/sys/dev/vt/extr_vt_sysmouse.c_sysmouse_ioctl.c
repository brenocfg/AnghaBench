#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dz; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  button; int /*<<< orphan*/  obutton; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ mousestatus_t ;
struct TYPE_6__ {int rate; int resolution; int level; int /*<<< orphan*/ * syncmask; int /*<<< orphan*/  packetsize; int /*<<< orphan*/  protocol; int /*<<< orphan*/  accelfactor; } ;
typedef  TYPE_2__ mousemode_t ;
struct TYPE_7__ {int buttons; int /*<<< orphan*/  hwid; int /*<<< orphan*/  model; int /*<<< orphan*/  type; int /*<<< orphan*/  iftype; } ;
typedef  TYPE_3__ mousehw_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTL ; 
#define  FIOASYNC 138 
#define  FIOGETOWN 137 
#define  FIONBIO 136 
#define  FIOSETOWN 135 
 int /*<<< orphan*/  IOCBASECMD (int) ; 
 scalar_t__ IOCGROUP (int) ; 
#define  MOUSE_GETHWINFO 134 
#define  MOUSE_GETLEVEL 133 
#define  MOUSE_GETMODE 132 
#define  MOUSE_GETSTATUS 131 
 int /*<<< orphan*/  MOUSE_IF_SYSMOUSE ; 
 int /*<<< orphan*/  MOUSE_MODEL_GENERIC ; 
 int /*<<< orphan*/  MOUSE_MOUSE ; 
#define  MOUSE_MOUSECHAR 130 
 int /*<<< orphan*/  MOUSE_MSC_PACKETSIZE ; 
 int /*<<< orphan*/  MOUSE_MSC_SYNC ; 
 int /*<<< orphan*/  MOUSE_MSC_SYNCMASK ; 
 int /*<<< orphan*/  MOUSE_PROTO_MSC ; 
 int /*<<< orphan*/  MOUSE_PROTO_SYSMOUSE ; 
#define  MOUSE_SETLEVEL 129 
#define  MOUSE_SETMODE 128 
 int /*<<< orphan*/  MOUSE_SYS_PACKETSIZE ; 
 int /*<<< orphan*/  MOUSE_SYS_SYNC ; 
 int /*<<< orphan*/  MOUSE_SYS_SYNCMASK ; 
 int /*<<< orphan*/  SM_ASYNC ; 
 int fgetown (int /*<<< orphan*/ *) ; 
 int fsetown (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysmouse_flags ; 
 int sysmouse_level ; 
 int /*<<< orphan*/  sysmouse_lock ; 
 int /*<<< orphan*/  sysmouse_sigio ; 
 TYPE_1__ sysmouse_status ; 

__attribute__((used)) static int
sysmouse_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flag,
    struct thread *td)
{

	switch (cmd) {
	case FIOASYNC:
		mtx_lock(&sysmouse_lock);
		if (*(int *)data)
			sysmouse_flags |= SM_ASYNC;
		else
			sysmouse_flags &= ~SM_ASYNC;
		mtx_unlock(&sysmouse_lock);
		return (0);
	case FIONBIO:
		return (0);
	case FIOGETOWN:
		*(int *)data = fgetown(&sysmouse_sigio);
		return (0);
	case FIOSETOWN:
		return (fsetown(*(int *)data, &sysmouse_sigio));
	case MOUSE_GETHWINFO: {
		mousehw_t *hw = (mousehw_t *)data;

		hw->buttons = 10;
		hw->iftype = MOUSE_IF_SYSMOUSE;
		hw->type = MOUSE_MOUSE;
		hw->model = MOUSE_MODEL_GENERIC;
		hw->hwid = 0;

		return (0);
	}
	case MOUSE_GETLEVEL:
		*(int *)data = sysmouse_level;
		return (0);
	case MOUSE_GETMODE: {
		mousemode_t *mode = (mousemode_t *)data;

		mode->rate = -1;
		mode->resolution = -1;
		mode->accelfactor = 0;
		mode->level = sysmouse_level;

		switch (mode->level) {
		case 0:
			mode->protocol = MOUSE_PROTO_MSC;
			mode->packetsize = MOUSE_MSC_PACKETSIZE;
			mode->syncmask[0] = MOUSE_MSC_SYNCMASK;
			mode->syncmask[1] = MOUSE_MSC_SYNC;
			break;
		case 1:
			mode->protocol = MOUSE_PROTO_SYSMOUSE;
			mode->packetsize = MOUSE_SYS_PACKETSIZE;
			mode->syncmask[0] = MOUSE_SYS_SYNCMASK;
			mode->syncmask[1] = MOUSE_SYS_SYNC;
			break;
		}

		return (0);
	}
	case MOUSE_GETSTATUS:
		mtx_lock(&sysmouse_lock);
		*(mousestatus_t *)data = sysmouse_status;

		sysmouse_status.flags = 0;
		sysmouse_status.obutton = sysmouse_status.button;
		sysmouse_status.dx = 0;
		sysmouse_status.dy = 0;
		sysmouse_status.dz = 0;
		mtx_unlock(&sysmouse_lock);

		return (0);
	case MOUSE_SETLEVEL: {
		int level;

		level = *(int *)data;
		if (level != 0 && level != 1)
			return (EINVAL);

		sysmouse_level = level;
		return (0);
	}
	case MOUSE_SETMODE: {
		mousemode_t *mode = (mousemode_t *)data;

		switch (mode->level) {
		case -1:
			/* Do nothing. */
			break;
		case 0:
		case 1:
			sysmouse_level = mode->level;
			break;
		default:
			return (EINVAL);
		}

		return (0);
	}
	case MOUSE_MOUSECHAR:
		return (0);
	default:
#ifdef VT_SYSMOUSE_DEBUG
		printf("sysmouse: unknown ioctl: %c:%lx\n",
		    (char)IOCGROUP(cmd), IOCBASECMD(cmd));
#endif
		return (ENOIOCTL);
	}
}