#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_10__ {int infoMajor; } ;
typedef  TYPE_2__ synapticshw_t ;
struct thread {int dummy; } ;
struct TYPE_15__ {int hwid; int /*<<< orphan*/  model; int /*<<< orphan*/  type; int /*<<< orphan*/  iftype; int /*<<< orphan*/  buttons; } ;
struct TYPE_14__ {int level; int rate; int resolution; int accelfactor; void* protocol; int /*<<< orphan*/ * syncmask; int /*<<< orphan*/  packetsize; } ;
struct TYPE_9__ {int rate; int resolution; } ;
struct TYPE_13__ {int /*<<< orphan*/  dz; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  button; int /*<<< orphan*/  obutton; int /*<<< orphan*/  flags; } ;
struct psm_softc {int flags; int /*<<< orphan*/  async; TYPE_7__ hw; int /*<<< orphan*/  kbdc; TYPE_6__ mode; TYPE_1__ dflt_mode; TYPE_5__ status; TYPE_2__ synhw; } ;
struct cdev {struct psm_softc* si_drv1; } ;
struct TYPE_11__ {int rate; int resolution; int accelfactor; void* protocol; } ;
typedef  TYPE_3__ old_mousemode_t ;
struct TYPE_12__ {int hwid; int /*<<< orphan*/  type; int /*<<< orphan*/  iftype; int /*<<< orphan*/  buttons; } ;
typedef  TYPE_4__ old_mousehw_t ;
typedef  TYPE_5__ mousestatus_t ;
typedef  TYPE_6__ mousemode_t ;
typedef  TYPE_7__ mousehw_t ;
struct TYPE_16__ {int len; int* buf; } ;
typedef  TYPE_8__ mousedata_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOTTY ; 
#define  FIOASYNC 150 
#define  FIOGETOWN 149 
#define  FIONBIO 148 
#define  FIOSETOWN 147 
#define  MOUSE_GETHWID 146 
#define  MOUSE_GETHWINFO 145 
#define  MOUSE_GETLEVEL 144 
#define  MOUSE_GETMODE 143 
#define  MOUSE_GETSTATUS 142 
 int /*<<< orphan*/  MOUSE_MODEL_GENERIC ; 
 void* MOUSE_PROTO_PS2 ; 
 void* MOUSE_PROTO_SYSMOUSE ; 
 int /*<<< orphan*/  MOUSE_PS2_PACKETSIZE ; 
#define  MOUSE_READDATA 141 
#define  MOUSE_READSTATE 140 
 int MOUSE_RES_DEFAULT ; 
 void* MOUSE_RES_HIGH ; 
 void* MOUSE_RES_LOW ; 
 void* MOUSE_RES_MEDIUMHIGH ; 
 void* MOUSE_RES_MEDIUMLOW ; 
#define  MOUSE_SETLEVEL 139 
#define  MOUSE_SETMODE 138 
#define  MOUSE_SETRATE 137 
#define  MOUSE_SETRESOLUTION 136 
#define  MOUSE_SETSCALING 135 
#define  MOUSE_SYN_GETHWINFO 134 
 int /*<<< orphan*/  MOUSE_SYS_PACKETSIZE ; 
 int /*<<< orphan*/  MOUSE_SYS_SYNC ; 
 int /*<<< orphan*/  MOUSE_SYS_SYNCMASK ; 
#define  OLD_MOUSE_GETHWINFO 133 
#define  OLD_MOUSE_GETMODE 132 
#define  OLD_MOUSE_SETMODE 131 
#define  PSM_LEVEL_BASE 130 
 int PSM_LEVEL_MAX ; 
 int PSM_LEVEL_MIN ; 
#define  PSM_LEVEL_NATIVE 129 
#define  PSM_LEVEL_STANDARD 128 
 int PSM_NEED_SYNCBITS ; 
 int UCHAR_MAX ; 
 int block_mouse_data (struct psm_softc*,int*) ; 
 int fgetown (int /*<<< orphan*/ *) ; 
 int fsetown (int,int /*<<< orphan*/ *) ; 
 int get_aux_id (int /*<<< orphan*/ ) ; 
 int get_mouse_status (int /*<<< orphan*/ ,int*,int,int) ; 
 void* set_mouse_resolution (int /*<<< orphan*/ ,void*) ; 
 void* set_mouse_sampling_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_mouse_scaling (int /*<<< orphan*/ ,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  unblock_mouse_data (struct psm_softc*,int) ; 

__attribute__((used)) static int
psmioctl(struct cdev *dev, u_long cmd, caddr_t addr, int flag,
    struct thread *td)
{
	struct psm_softc *sc = dev->si_drv1;
	mousemode_t mode;
	mousestatus_t status;
	mousedata_t *data;
	int stat[3];
	int command_byte;
	int error = 0;
	int s;

	/* Perform IOCTL command */
	switch (cmd) {

	case OLD_MOUSE_GETHWINFO:
		s = spltty();
		((old_mousehw_t *)addr)->buttons = sc->hw.buttons;
		((old_mousehw_t *)addr)->iftype = sc->hw.iftype;
		((old_mousehw_t *)addr)->type = sc->hw.type;
		((old_mousehw_t *)addr)->hwid = sc->hw.hwid & 0x00ff;
		splx(s);
		break;

	case MOUSE_GETHWINFO:
		s = spltty();
		*(mousehw_t *)addr = sc->hw;
		if (sc->mode.level == PSM_LEVEL_BASE)
			((mousehw_t *)addr)->model = MOUSE_MODEL_GENERIC;
		splx(s);
		break;

	case MOUSE_SYN_GETHWINFO:
		s = spltty();
		if (sc->synhw.infoMajor >= 4)
			*(synapticshw_t *)addr = sc->synhw;
		else
			error = EINVAL;
		splx(s);
		break;

	case OLD_MOUSE_GETMODE:
		s = spltty();
		switch (sc->mode.level) {
		case PSM_LEVEL_BASE:
			((old_mousemode_t *)addr)->protocol = MOUSE_PROTO_PS2;
			break;
		case PSM_LEVEL_STANDARD:
			((old_mousemode_t *)addr)->protocol =
			    MOUSE_PROTO_SYSMOUSE;
			break;
		case PSM_LEVEL_NATIVE:
			((old_mousemode_t *)addr)->protocol = MOUSE_PROTO_PS2;
			break;
		}
		((old_mousemode_t *)addr)->rate = sc->mode.rate;
		((old_mousemode_t *)addr)->resolution = sc->mode.resolution;
		((old_mousemode_t *)addr)->accelfactor = sc->mode.accelfactor;
		splx(s);
		break;

	case MOUSE_GETMODE:
		s = spltty();
		*(mousemode_t *)addr = sc->mode;
		if ((sc->flags & PSM_NEED_SYNCBITS) != 0) {
			((mousemode_t *)addr)->syncmask[0] = 0;
			((mousemode_t *)addr)->syncmask[1] = 0;
		}
		((mousemode_t *)addr)->resolution =
			MOUSE_RES_LOW - sc->mode.resolution;
		switch (sc->mode.level) {
		case PSM_LEVEL_BASE:
			((mousemode_t *)addr)->protocol = MOUSE_PROTO_PS2;
			((mousemode_t *)addr)->packetsize =
			    MOUSE_PS2_PACKETSIZE;
			break;
		case PSM_LEVEL_STANDARD:
			((mousemode_t *)addr)->protocol = MOUSE_PROTO_SYSMOUSE;
			((mousemode_t *)addr)->packetsize =
			    MOUSE_SYS_PACKETSIZE;
			((mousemode_t *)addr)->syncmask[0] = MOUSE_SYS_SYNCMASK;
			((mousemode_t *)addr)->syncmask[1] = MOUSE_SYS_SYNC;
			break;
		case PSM_LEVEL_NATIVE:
			/* FIXME: this isn't quite correct... XXX */
			((mousemode_t *)addr)->protocol = MOUSE_PROTO_PS2;
			break;
		}
		splx(s);
		break;

	case OLD_MOUSE_SETMODE:
	case MOUSE_SETMODE:
		if (cmd == OLD_MOUSE_SETMODE) {
			mode.rate = ((old_mousemode_t *)addr)->rate;
			/*
			 * resolution  old I/F   new I/F
			 * default        0         0
			 * low            1        -2
			 * medium low     2        -3
			 * medium high    3        -4
			 * high           4        -5
			 */
			if (((old_mousemode_t *)addr)->resolution > 0)
				mode.resolution =
				    -((old_mousemode_t *)addr)->resolution - 1;
			else
				mode.resolution = 0;
			mode.accelfactor =
			    ((old_mousemode_t *)addr)->accelfactor;
			mode.level = -1;
		} else
			mode = *(mousemode_t *)addr;

		/* adjust and validate parameters. */
		if (mode.rate > UCHAR_MAX)
			return (EINVAL);
		if (mode.rate == 0)
			mode.rate = sc->dflt_mode.rate;
		else if (mode.rate == -1)
			/* don't change the current setting */
			;
		else if (mode.rate < 0)
			return (EINVAL);
		if (mode.resolution >= UCHAR_MAX)
			return (EINVAL);
		if (mode.resolution >= 200)
			mode.resolution = MOUSE_RES_HIGH;
		else if (mode.resolution >= 100)
			mode.resolution = MOUSE_RES_MEDIUMHIGH;
		else if (mode.resolution >= 50)
			mode.resolution = MOUSE_RES_MEDIUMLOW;
		else if (mode.resolution > 0)
			mode.resolution = MOUSE_RES_LOW;
		if (mode.resolution == MOUSE_RES_DEFAULT)
			mode.resolution = sc->dflt_mode.resolution;
		else if (mode.resolution == -1)
			/* don't change the current setting */
			;
		else if (mode.resolution < 0) /* MOUSE_RES_LOW/MEDIUM/HIGH */
			mode.resolution = MOUSE_RES_LOW - mode.resolution;
		if (mode.level == -1)
			/* don't change the current setting */
			mode.level = sc->mode.level;
		else if ((mode.level < PSM_LEVEL_MIN) ||
		    (mode.level > PSM_LEVEL_MAX))
			return (EINVAL);
		if (mode.accelfactor == -1)
			/* don't change the current setting */
			mode.accelfactor = sc->mode.accelfactor;
		else if (mode.accelfactor < 0)
			return (EINVAL);

		/* don't allow anybody to poll the keyboard controller */
		error = block_mouse_data(sc, &command_byte);
		if (error)
			return (error);

		/* set mouse parameters */
		if (mode.rate > 0)
			mode.rate = set_mouse_sampling_rate(sc->kbdc,
			    mode.rate);
		if (mode.resolution >= 0)
			mode.resolution =
			    set_mouse_resolution(sc->kbdc, mode.resolution);
		set_mouse_scaling(sc->kbdc, 1);
		get_mouse_status(sc->kbdc, stat, 0, 3);

		s = spltty();
		sc->mode.rate = mode.rate;
		sc->mode.resolution = mode.resolution;
		sc->mode.accelfactor = mode.accelfactor;
		sc->mode.level = mode.level;
		splx(s);

		unblock_mouse_data(sc, command_byte);
		break;

	case MOUSE_GETLEVEL:
		*(int *)addr = sc->mode.level;
		break;

	case MOUSE_SETLEVEL:
		if ((*(int *)addr < PSM_LEVEL_MIN) ||
		    (*(int *)addr > PSM_LEVEL_MAX))
			return (EINVAL);
		sc->mode.level = *(int *)addr;
		break;

	case MOUSE_GETSTATUS:
		s = spltty();
		status = sc->status;
		sc->status.flags = 0;
		sc->status.obutton = sc->status.button;
		sc->status.button = 0;
		sc->status.dx = 0;
		sc->status.dy = 0;
		sc->status.dz = 0;
		splx(s);
		*(mousestatus_t *)addr = status;
		break;

	case MOUSE_READSTATE:
	case MOUSE_READDATA:
		data = (mousedata_t *)addr;
		if (data->len > sizeof(data->buf)/sizeof(data->buf[0]))
			return (EINVAL);

		error = block_mouse_data(sc, &command_byte);
		if (error)
			return (error);
		if ((data->len = get_mouse_status(sc->kbdc, data->buf,
		    (cmd == MOUSE_READDATA) ? 1 : 0, data->len)) <= 0)
			error = EIO;
		unblock_mouse_data(sc, command_byte);
		break;

#if (defined(MOUSE_SETRESOLUTION))
	case MOUSE_SETRESOLUTION:
		mode.resolution = *(int *)addr;
		if (mode.resolution >= UCHAR_MAX)
			return (EINVAL);
		else if (mode.resolution >= 200)
			mode.resolution = MOUSE_RES_HIGH;
		else if (mode.resolution >= 100)
			mode.resolution = MOUSE_RES_MEDIUMHIGH;
		else if (mode.resolution >= 50)
			mode.resolution = MOUSE_RES_MEDIUMLOW;
		else if (mode.resolution > 0)
			mode.resolution = MOUSE_RES_LOW;
		if (mode.resolution == MOUSE_RES_DEFAULT)
			mode.resolution = sc->dflt_mode.resolution;
		else if (mode.resolution == -1)
			mode.resolution = sc->mode.resolution;
		else if (mode.resolution < 0) /* MOUSE_RES_LOW/MEDIUM/HIGH */
			mode.resolution = MOUSE_RES_LOW - mode.resolution;

		error = block_mouse_data(sc, &command_byte);
		if (error)
			return (error);
		sc->mode.resolution =
		    set_mouse_resolution(sc->kbdc, mode.resolution);
		if (sc->mode.resolution != mode.resolution)
			error = EIO;
		unblock_mouse_data(sc, command_byte);
		break;
#endif /* MOUSE_SETRESOLUTION */

#if (defined(MOUSE_SETRATE))
	case MOUSE_SETRATE:
		mode.rate = *(int *)addr;
		if (mode.rate > UCHAR_MAX)
			return (EINVAL);
		if (mode.rate == 0)
			mode.rate = sc->dflt_mode.rate;
		else if (mode.rate < 0)
			mode.rate = sc->mode.rate;

		error = block_mouse_data(sc, &command_byte);
		if (error)
			return (error);
		sc->mode.rate = set_mouse_sampling_rate(sc->kbdc, mode.rate);
		if (sc->mode.rate != mode.rate)
			error = EIO;
		unblock_mouse_data(sc, command_byte);
		break;
#endif /* MOUSE_SETRATE */

#if (defined(MOUSE_SETSCALING))
	case MOUSE_SETSCALING:
		if ((*(int *)addr <= 0) || (*(int *)addr > 2))
			return (EINVAL);

		error = block_mouse_data(sc, &command_byte);
		if (error)
			return (error);
		if (!set_mouse_scaling(sc->kbdc, *(int *)addr))
			error = EIO;
		unblock_mouse_data(sc, command_byte);
		break;
#endif /* MOUSE_SETSCALING */

#if (defined(MOUSE_GETHWID))
	case MOUSE_GETHWID:
		error = block_mouse_data(sc, &command_byte);
		if (error)
			return (error);
		sc->hw.hwid &= ~0x00ff;
		sc->hw.hwid |= get_aux_id(sc->kbdc);
		*(int *)addr = sc->hw.hwid & 0x00ff;
		unblock_mouse_data(sc, command_byte);
		break;
#endif /* MOUSE_GETHWID */

	case FIONBIO:
	case FIOASYNC:
		break;
	case FIOSETOWN:
		error = fsetown(*(int *)addr, &sc->async);
		break;
	case FIOGETOWN:
		*(int *) addr = fgetown(&sc->async);
		break;
	default:
		return (ENOTTY);
	}

	return (error);
}