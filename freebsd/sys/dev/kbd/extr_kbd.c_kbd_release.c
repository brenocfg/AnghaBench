#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * kc_arg; int /*<<< orphan*/ * kc_func; } ;
struct TYPE_9__ {void* kb_token; TYPE_1__ kb_callback; } ;
typedef  TYPE_2__ keyboard_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  KBD_IS_BUSY (TYPE_2__*) ; 
 int /*<<< orphan*/  KBD_IS_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  KBD_UNBUSY (TYPE_2__*) ; 
 int /*<<< orphan*/  kbdd_clear_state (TYPE_2__*) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

int
kbd_release(keyboard_t *kbd, void *id)
{
	int error;
	int s;

	s = spltty();
	if (!KBD_IS_VALID(kbd) || !KBD_IS_BUSY(kbd)) {
		error = EINVAL;
	} else if (kbd->kb_token != id) {
		error = EPERM;
	} else {
		kbd->kb_token = NULL;
		KBD_UNBUSY(kbd);
		kbd->kb_callback.kc_func = NULL;
		kbd->kb_callback.kc_arg = NULL;
		kbdd_clear_state(kbd);
		error = 0;
	}
	splx(s);
	return (error);
}