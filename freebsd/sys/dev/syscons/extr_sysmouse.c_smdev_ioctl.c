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
struct tty {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dz; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  button; int /*<<< orphan*/  obutton; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ mousestatus_t ;
struct TYPE_6__ {int level; int rate; int resolution; int /*<<< orphan*/ * syncmask; int /*<<< orphan*/  packetsize; int /*<<< orphan*/  accelfactor; int /*<<< orphan*/  protocol; } ;
typedef  TYPE_2__ mousemode_t ;
struct TYPE_7__ {int buttons; int /*<<< orphan*/  hwid; int /*<<< orphan*/  model; int /*<<< orphan*/  type; int /*<<< orphan*/  iftype; } ;
typedef  TYPE_3__ mousehw_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOIOCTL ; 
#define  MOUSE_GETHWINFO 135 
#define  MOUSE_GETLEVEL 134 
#define  MOUSE_GETMODE 133 
#define  MOUSE_GETSTATUS 132 
 int /*<<< orphan*/  MOUSE_IF_SYSMOUSE ; 
 int /*<<< orphan*/  MOUSE_MODEL_GENERIC ; 
 int /*<<< orphan*/  MOUSE_MOUSE ; 
 int /*<<< orphan*/  MOUSE_MSC_PACKETSIZE ; 
 int /*<<< orphan*/  MOUSE_MSC_SYNC ; 
 int /*<<< orphan*/  MOUSE_MSC_SYNCMASK ; 
 int /*<<< orphan*/  MOUSE_PROTO_MSC ; 
 int /*<<< orphan*/  MOUSE_PROTO_SYSMOUSE ; 
#define  MOUSE_READDATA 131 
#define  MOUSE_READSTATE 130 
#define  MOUSE_SETLEVEL 129 
#define  MOUSE_SETMODE 128 
 int /*<<< orphan*/  MOUSE_SYS_PACKETSIZE ; 
 int /*<<< orphan*/  MOUSE_SYS_SYNC ; 
 int /*<<< orphan*/  MOUSE_SYS_SYNCMASK ; 
 int mouse_level ; 
 TYPE_1__ mouse_status ; 

__attribute__((used)) static int
smdev_ioctl(struct tty *tp, u_long cmd, caddr_t data, struct thread *td)
{
	mousehw_t *hw;
	mousemode_t *mode;

	switch (cmd) {

	case MOUSE_GETHWINFO:	/* get device information */
		hw = (mousehw_t *)data;
		hw->buttons = 10;		/* XXX unknown */
		hw->iftype = MOUSE_IF_SYSMOUSE;
		hw->type = MOUSE_MOUSE;
		hw->model = MOUSE_MODEL_GENERIC;
		hw->hwid = 0;
		return 0;

	case MOUSE_GETMODE:	/* get protocol/mode */
		mode = (mousemode_t *)data;
		mode->level = mouse_level;
		switch (mode->level) {
		case 0: /* emulate MouseSystems protocol */
			mode->protocol = MOUSE_PROTO_MSC;
			mode->rate = -1;		/* unknown */
			mode->resolution = -1;	/* unknown */
			mode->accelfactor = 0;	/* disabled */
			mode->packetsize = MOUSE_MSC_PACKETSIZE;
			mode->syncmask[0] = MOUSE_MSC_SYNCMASK;
			mode->syncmask[1] = MOUSE_MSC_SYNC;
			break;

		case 1: /* sysmouse protocol */
			mode->protocol = MOUSE_PROTO_SYSMOUSE;
			mode->rate = -1;
			mode->resolution = -1;
			mode->accelfactor = 0;
			mode->packetsize = MOUSE_SYS_PACKETSIZE;
			mode->syncmask[0] = MOUSE_SYS_SYNCMASK;
			mode->syncmask[1] = MOUSE_SYS_SYNC;
			break;
		}
		return 0;

	case MOUSE_SETMODE:	/* set protocol/mode */
		mode = (mousemode_t *)data;
		if (mode->level == -1)
			; 	/* don't change the current setting */
		else if ((mode->level < 0) || (mode->level > 1))
			return EINVAL;
		else
			mouse_level = mode->level;
		return 0;

	case MOUSE_GETLEVEL:	/* get operation level */
		*(int *)data = mouse_level;
		return 0;

	case MOUSE_SETLEVEL:	/* set operation level */
		if ((*(int *)data  < 0) || (*(int *)data > 1))
			return EINVAL;
		mouse_level = *(int *)data;
		return 0;

	case MOUSE_GETSTATUS:	/* get accumulated mouse events */
		*(mousestatus_t *)data = mouse_status;
		mouse_status.flags = 0;
		mouse_status.obutton = mouse_status.button;
		mouse_status.dx = 0;
		mouse_status.dy = 0;
		mouse_status.dz = 0;
		return 0;

	case MOUSE_READSTATE:	/* read status from the device */
	case MOUSE_READDATA:	/* read data from the device */
		return ENODEV;
	}

	return (ENOIOCTL);
}