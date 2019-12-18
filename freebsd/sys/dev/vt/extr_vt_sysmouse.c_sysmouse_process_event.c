#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int id; int /*<<< orphan*/  value; } ;
struct TYPE_8__ {int buttons; int x; int y; int z; } ;
struct TYPE_10__ {TYPE_2__ event; TYPE_1__ data; } ;
struct TYPE_11__ {int operation; TYPE_3__ u; } ;
typedef  TYPE_4__ mouse_info_t ;
struct TYPE_12__ {int button; int dx; int dy; int dz; int flags; int obutton; } ;

/* Variables and functions */
#define  MOUSE_ACTION 133 
#define  MOUSE_BUTTON_EVENT 132 
#define  MOUSE_MOTION_EVENT 131 
#define  MOUSE_MSC_BUTTON1UP 130 
#define  MOUSE_MSC_BUTTON2UP 129 
#define  MOUSE_MSC_BUTTON3UP 128 
 int const MOUSE_MSC_SYNC ; 
 int MOUSE_POSCHANGED ; 
 size_t MOUSE_STDBUTTONS ; 
 int MOUSE_SYS_PACKETSIZE ; 
 int /*<<< orphan*/  RANDOM_MOUSE ; 
 int imax (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imin (int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_harvest_queue (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysmouse_buf_store (unsigned char*) ; 
 int /*<<< orphan*/  sysmouse_evdev_store (int,int,int,int) ; 
 int /*<<< orphan*/  sysmouse_level ; 
 int /*<<< orphan*/  sysmouse_lock ; 
 TYPE_5__ sysmouse_status ; 
 int /*<<< orphan*/  vt_mouse_event (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sysmouse_process_event(mouse_info_t *mi)
{
	/* MOUSE_BUTTON?DOWN -> MOUSE_MSC_BUTTON?UP */
	static const int buttonmap[8] = {
	    MOUSE_MSC_BUTTON1UP | MOUSE_MSC_BUTTON2UP | MOUSE_MSC_BUTTON3UP,
	    MOUSE_MSC_BUTTON2UP | MOUSE_MSC_BUTTON3UP,
	    MOUSE_MSC_BUTTON1UP | MOUSE_MSC_BUTTON3UP,
	    MOUSE_MSC_BUTTON3UP,
	    MOUSE_MSC_BUTTON1UP | MOUSE_MSC_BUTTON2UP,
	    MOUSE_MSC_BUTTON2UP,
	    MOUSE_MSC_BUTTON1UP,
	    0,
	};
	unsigned char buf[MOUSE_SYS_PACKETSIZE];
	int x, y, iy, z;

	random_harvest_queue(mi, sizeof *mi, RANDOM_MOUSE);

	mtx_lock(&sysmouse_lock);
	switch (mi->operation) {
	case MOUSE_ACTION:
		sysmouse_status.button = mi->u.data.buttons;
		/* FALLTHROUGH */
	case MOUSE_MOTION_EVENT:
		x = mi->u.data.x;
		y = mi->u.data.y;
		z = mi->u.data.z;
		break;
	case MOUSE_BUTTON_EVENT:
		x = y = z = 0;
		if (mi->u.event.value > 0)
			sysmouse_status.button |= mi->u.event.id;
		else
			sysmouse_status.button &= ~mi->u.event.id;
		break;
	default:
		goto done;
	}

	sysmouse_status.dx += x;
	sysmouse_status.dy += y;
	sysmouse_status.dz += z;
	sysmouse_status.flags |= ((x || y || z) ? MOUSE_POSCHANGED : 0) |
	    (sysmouse_status.obutton ^ sysmouse_status.button);
	if (sysmouse_status.flags == 0)
		goto done;

#ifdef EVDEV_SUPPORT
	sysmouse_evdev_store(x, y, z, sysmouse_status.button);
#endif

	/* The first five bytes are compatible with MouseSystems. */
	buf[0] = MOUSE_MSC_SYNC |
	    buttonmap[sysmouse_status.button & MOUSE_STDBUTTONS];
	x = imax(imin(x, 255), -256);
	buf[1] = x >> 1;
	buf[3] = x - buf[1];
	iy = -imax(imin(y, 255), -256);
	buf[2] = iy >> 1;
	buf[4] = iy - buf[2];
	/* Extended part. */
        z = imax(imin(z, 127), -128);
        buf[5] = (z >> 1) & 0x7f;
        buf[6] = (z - (z >> 1)) & 0x7f;
        /* Buttons 4-10. */
        buf[7] = (~sysmouse_status.button >> 3) & 0x7f;

	sysmouse_buf_store(buf);

#ifndef SC_NO_CUTPASTE
	mtx_unlock(&sysmouse_lock);
	vt_mouse_event(mi->operation, x, y, mi->u.event.id, mi->u.event.value,
	    sysmouse_level);
	return;
#endif

done:	mtx_unlock(&sysmouse_lock);
}