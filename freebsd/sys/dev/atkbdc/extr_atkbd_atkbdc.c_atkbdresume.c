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
struct TYPE_8__ {int /*<<< orphan*/  kb_flags; } ;
typedef  TYPE_1__ keyboard_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_9__ {int /*<<< orphan*/  intr; } ;
typedef  TYPE_2__ atkbd_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATKBD_DRIVER_NAME ; 
 int /*<<< orphan*/  KB_INITIALIZED ; 
 int /*<<< orphan*/  device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 TYPE_2__* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_find_keyboard (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* kbd_get_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdd_clear_state (TYPE_1__*) ; 
 int /*<<< orphan*/  kbdd_init (TYPE_1__*,int,TYPE_1__**,int*,int /*<<< orphan*/ ) ; 
 int rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atkbdresume(device_t dev)
{
	atkbd_softc_t *sc;
	keyboard_t *kbd;
	int args[2];

	sc = device_get_softc(dev);
	kbd = kbd_get_keyboard(kbd_find_keyboard(ATKBD_DRIVER_NAME,
						 device_get_unit(dev)));
	if (kbd) {
		kbd->kb_flags &= ~KB_INITIALIZED;
		args[0] = device_get_unit(device_get_parent(dev));
		args[1] = rman_get_start(sc->intr);
		kbdd_init(kbd, device_get_unit(dev), &kbd, args,
		    device_get_flags(dev));
		kbdd_clear_state(kbd);
	}
	return 0;
}