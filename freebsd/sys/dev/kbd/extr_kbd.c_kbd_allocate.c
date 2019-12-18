#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kbd_callback_func_t ;
struct TYPE_6__ {void* kc_arg; int /*<<< orphan*/ * kc_func; } ;
struct TYPE_7__ {TYPE_1__ kb_callback; void* kb_token; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBD_BUSY (TYPE_2__*) ; 
 scalar_t__ KBD_IS_BUSY (TYPE_2__*) ; 
 int kbd_find_keyboard (char*,int) ; 
 int /*<<< orphan*/  kbdd_clear_state (TYPE_2__*) ; 
 TYPE_2__** keyboard ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

int
kbd_allocate(char *driver, int unit, void *id, kbd_callback_func_t *func,
	     void *arg)
{
	int index;
	int s;

	if (func == NULL)
		return (-1);

	s = spltty();
	index = kbd_find_keyboard(driver, unit);
	if (index >= 0) {
		if (KBD_IS_BUSY(keyboard[index])) {
			splx(s);
			return (-1);
		}
		keyboard[index]->kb_token = id;
		KBD_BUSY(keyboard[index]);
		keyboard[index]->kb_callback.kc_func = func;
		keyboard[index]->kb_callback.kc_arg = arg;
		kbdd_clear_state(keyboard[index]);
	}
	splx(s);
	return (index);
}