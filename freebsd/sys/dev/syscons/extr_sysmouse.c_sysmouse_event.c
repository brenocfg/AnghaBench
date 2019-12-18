#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_8__ {int id; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int buttons; int x; int y; int z; } ;
struct TYPE_9__ {TYPE_2__ event; TYPE_1__ data; } ;
struct TYPE_10__ {int operation; TYPE_3__ u; } ;
typedef  TYPE_4__ mouse_info_t ;
struct TYPE_11__ {int button; int dx; int dy; int dz; int flags; int obutton; } ;

/* Variables and functions */
#define  MOUSE_ACTION 133 
#define  MOUSE_BUTTON_EVENT 132 
#define  MOUSE_MOTION_EVENT 131 
#define  MOUSE_MSC_BUTTON1UP 130 
#define  MOUSE_MSC_BUTTON2UP 129 
#define  MOUSE_MSC_BUTTON3UP 128 
 int MOUSE_MSC_PACKETSIZE ; 
 int MOUSE_MSC_SYNC ; 
 int MOUSE_POSCHANGED ; 
 size_t MOUSE_STDBUTTONS ; 
 int MOUSE_SYS_PACKETSIZE ; 
 int imax (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imin (int,int) ; 
 int mouse_level ; 
 TYPE_6__ mouse_status ; 
 int /*<<< orphan*/  smdev_evdev_write (int,int,int,int) ; 
 int /*<<< orphan*/  sysmouse_tty ; 
 int /*<<< orphan*/  tty_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_opened (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (int /*<<< orphan*/ ) ; 

int
sysmouse_event(mouse_info_t *info)
{
	/* MOUSE_BUTTON?DOWN -> MOUSE_MSC_BUTTON?UP */
	static int butmap[8] = {
	    MOUSE_MSC_BUTTON1UP | MOUSE_MSC_BUTTON2UP | MOUSE_MSC_BUTTON3UP,
	    MOUSE_MSC_BUTTON2UP | MOUSE_MSC_BUTTON3UP,
	    MOUSE_MSC_BUTTON1UP | MOUSE_MSC_BUTTON3UP,
	    MOUSE_MSC_BUTTON3UP,
	    MOUSE_MSC_BUTTON1UP | MOUSE_MSC_BUTTON2UP,
	    MOUSE_MSC_BUTTON2UP,
	    MOUSE_MSC_BUTTON1UP,
	    0,
	};
	u_char buf[8];
	int x, y, z;
	int i, flags = 0;

	tty_lock(sysmouse_tty);

	switch (info->operation) {
	case MOUSE_ACTION:
        	mouse_status.button = info->u.data.buttons;
		/* FALL THROUGH */
	case MOUSE_MOTION_EVENT:
		x = info->u.data.x;
		y = info->u.data.y;
		z = info->u.data.z;
		break;
	case MOUSE_BUTTON_EVENT:
		x = y = z = 0;
		if (info->u.event.value > 0)
			mouse_status.button |= info->u.event.id;
		else
			mouse_status.button &= ~info->u.event.id;
		break;
	default:
		goto done;
	}

	mouse_status.dx += x;
	mouse_status.dy += y;
	mouse_status.dz += z;
	mouse_status.flags |= ((x || y || z) ? MOUSE_POSCHANGED : 0)
			      | (mouse_status.obutton ^ mouse_status.button);
	flags = mouse_status.flags;
	if (flags == 0)
		goto done;

#ifdef EVDEV_SUPPORT
	smdev_evdev_write(x, y, z, mouse_status.button);
#endif

	if (!tty_opened(sysmouse_tty))
		goto done;

	/* the first five bytes are compatible with MouseSystems' */
	buf[0] = MOUSE_MSC_SYNC
		 | butmap[mouse_status.button & MOUSE_STDBUTTONS];
	x = imax(imin(x, 255), -256);
	buf[1] = x >> 1;
	buf[3] = x - buf[1];
	y = -imax(imin(y, 255), -256);
	buf[2] = y >> 1;
	buf[4] = y - buf[2];
	for (i = 0; i < MOUSE_MSC_PACKETSIZE; ++i)
		ttydisc_rint(sysmouse_tty, buf[i], 0);
	if (mouse_level >= 1) {
		/* extended part */
        	z = imax(imin(z, 127), -128);
        	buf[5] = (z >> 1) & 0x7f;
        	buf[6] = (z - (z >> 1)) & 0x7f;
        	/* buttons 4-10 */
        	buf[7] = (~mouse_status.button >> 3) & 0x7f;
        	for (i = MOUSE_MSC_PACKETSIZE; i < MOUSE_SYS_PACKETSIZE; ++i)
			ttydisc_rint(sysmouse_tty, buf[i], 0);
	}
	ttydisc_rint_done(sysmouse_tty);

done:	tty_unlock(sysmouse_tty);
	return (flags);
}