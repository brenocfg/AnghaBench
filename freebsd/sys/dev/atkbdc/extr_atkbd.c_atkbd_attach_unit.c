#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_13__ {int (* probe ) (int,int*,int) ;int (* init ) (int,TYPE_1__**,int*,int) ;int /*<<< orphan*/  (* diag ) (TYPE_1__*,scalar_t__) ;int /*<<< orphan*/  (* enable ) (TYPE_1__*) ;} ;
typedef  TYPE_2__ keyboard_switch_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_14__ {int /*<<< orphan*/  ks_timer; } ;
typedef  TYPE_3__ atkbd_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATKBD_DRIVER_NAME ; 
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_DEFAULT ; 
 int /*<<< orphan*/  atkbd_shutdown_final ; 
 int /*<<< orphan*/  atkbd_timeout (TYPE_1__*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int kbd_attach (TYPE_1__*) ; 
 TYPE_2__* kbd_get_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int stub1 (int,int*,int) ; 
 int stub2 (int,TYPE_1__**,int*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,scalar_t__) ; 

int
atkbd_attach_unit(device_t dev, keyboard_t **kbd, int irq, int flags)
{
	keyboard_switch_t *sw;
	atkbd_state_t *state;
	int args[2];
	int error;
	int unit;

	sw = kbd_get_switch(ATKBD_DRIVER_NAME);
	if (sw == NULL)
		return ENXIO;

	/* reset, initialize and enable the device */
	unit = device_get_unit(dev);
	args[0] = device_get_unit(device_get_parent(dev));
	args[1] = irq;
	*kbd = NULL;
	error = (*sw->probe)(unit, args, flags);
	if (error)
		return error;
	error = (*sw->init)(unit, kbd, args, flags);
	if (error)
		return error;
	(*sw->enable)(*kbd);

#ifdef KBD_INSTALL_CDEV
	/* attach a virtual keyboard cdev */
	error = kbd_attach(*kbd);
	if (error)
		return error;
#endif

	/*
	 * This is a kludge to compensate for lost keyboard interrupts.
	 * A similar code used to be in syscons. See below. XXX
	 */
	state = (atkbd_state_t *)(*kbd)->kb_data;
	callout_init(&state->ks_timer, 0);
	atkbd_timeout(*kbd);

	if (bootverbose)
		(*sw->diag)(*kbd, bootverbose);

	EVENTHANDLER_REGISTER(shutdown_final, atkbd_shutdown_final, *kbd,
	    SHUTDOWN_PRI_DEFAULT);

	return 0;
}