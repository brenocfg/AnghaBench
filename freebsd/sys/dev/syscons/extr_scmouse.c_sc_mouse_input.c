#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scr_stat ;
struct TYPE_6__ {int /*<<< orphan*/  z; } ;
struct TYPE_8__ {int id; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {TYPE_1__ data; TYPE_3__ event; } ;
struct TYPE_9__ {int operation; TYPE_2__ u; } ;
typedef  TYPE_4__ mouse_info_t ;

/* Variables and functions */
 int MOUSE_BUTTON1DOWN ; 
 int MOUSE_BUTTON2DOWN ; 
 int MOUSE_BUTTON3DOWN ; 
#define  MOUSE_BUTTON_EVENT 129 
#define  MOUSE_MOTION_EVENT 128 
 int /*<<< orphan*/  sc_mouse_input_button (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
sc_mouse_input(scr_stat *scp, mouse_info_t *mouse)
{

	switch (mouse->operation) {
	case MOUSE_BUTTON_EVENT:
		if (mouse->u.event.value > 0) {
			/* Mouse button pressed. */
			if (mouse->u.event.id & MOUSE_BUTTON1DOWN)
				sc_mouse_input_button(scp, 0);
			if (mouse->u.event.id & MOUSE_BUTTON2DOWN)
				sc_mouse_input_button(scp, 1);
			if (mouse->u.event.id & MOUSE_BUTTON3DOWN)
				sc_mouse_input_button(scp, 2);
		} else {
			/* Mouse button released. */
			sc_mouse_input_button(scp, 3);
		}
		break;
	case MOUSE_MOTION_EVENT:
		if (mouse->u.data.z < 0) {
			/* Scroll up. */
			sc_mouse_input_button(scp, 64);
		} else if (mouse->u.data.z > 0) {
			/* Scroll down. */
			sc_mouse_input_button(scp, 65);
		}
		break;
	}
}