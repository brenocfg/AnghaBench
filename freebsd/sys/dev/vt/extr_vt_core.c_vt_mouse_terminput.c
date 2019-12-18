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
struct vt_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  z; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 int MOUSE_BUTTON1DOWN ; 
 int MOUSE_BUTTON2DOWN ; 
 int MOUSE_BUTTON3DOWN ; 
#define  MOUSE_BUTTON_EVENT 129 
#define  MOUSE_MOTION_EVENT 128 
 TYPE_3__* mouse ; 
 int /*<<< orphan*/  sc_mouse_input_button (struct vt_device*,int) ; 
 int /*<<< orphan*/  vt_mouse_terminput_button (struct vt_device*,int) ; 

__attribute__((used)) static void
vt_mouse_terminput(struct vt_device *vd, int type, int x, int y, int event,
    int cnt)
{

	switch (type) {
	case MOUSE_BUTTON_EVENT:
		if (cnt > 0) {
			/* Mouse button pressed. */
			if (event & MOUSE_BUTTON1DOWN)
				vt_mouse_terminput_button(vd, 0);
			if (event & MOUSE_BUTTON2DOWN)
				vt_mouse_terminput_button(vd, 1);
			if (event & MOUSE_BUTTON3DOWN)
				vt_mouse_terminput_button(vd, 2);
		} else {
			/* Mouse button released. */
			vt_mouse_terminput_button(vd, 3);
		}
		break;
#ifdef notyet
	case MOUSE_MOTION_EVENT:
		if (mouse->u.data.z < 0) {
			/* Scroll up. */
			sc_mouse_input_button(vd, 64);
		} else if (mouse->u.data.z > 0) {
			/* Scroll down. */
			sc_mouse_input_button(vd, 65);
		}
		break;
#endif
	}
}