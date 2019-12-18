#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kb_flags; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATKBD_DEFAULT ; 
 int /*<<< orphan*/  ATKBD_DRIVER_NAME ; 
 int /*<<< orphan*/  KB_REGISTERED ; 
 scalar_t__ atkbd_init (int /*<<< orphan*/ ,TYPE_1__**,int*,int) ; 
 scalar_t__ atkbd_probe (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ atkbdc_configure () ; 
 int kbd_find_keyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* kbd_get_keyboard (int) ; 
 int /*<<< orphan*/  kbd_unregister (TYPE_1__*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_int_value (char*,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
atkbd_configure(int flags)
{
	keyboard_t *kbd;
	int arg[2];
	int i;

	/*
	 * Probe the keyboard controller, if not present or if the driver
	 * is disabled, unregister the keyboard if any.
	 */
	if (atkbdc_configure() != 0 ||
	    resource_disabled("atkbd", ATKBD_DEFAULT)) {
		i = kbd_find_keyboard(ATKBD_DRIVER_NAME, ATKBD_DEFAULT);
		if (i >= 0) {
			kbd = kbd_get_keyboard(i);
			kbd_unregister(kbd);
			kbd->kb_flags &= ~KB_REGISTERED;
		}
		return 0;
	}
	
	/* XXX: a kludge to obtain the device configuration flags */
	if (resource_int_value("atkbd", ATKBD_DEFAULT, "flags", &i) == 0)
		flags |= i;

	/* probe the default keyboard */
	arg[0] = -1;
	arg[1] = -1;
	kbd = NULL;
	if (atkbd_probe(ATKBD_DEFAULT, arg, flags))
		return 0;
	if (atkbd_init(ATKBD_DEFAULT, &kbd, arg, flags))
		return 0;

	/* return the number of found keyboards */
	return 1;
}