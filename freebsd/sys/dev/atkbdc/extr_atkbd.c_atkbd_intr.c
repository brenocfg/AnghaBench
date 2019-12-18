#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  kc_arg; int /*<<< orphan*/  (* kc_func ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int kb_delay1; int kb_delay2; TYPE_1__ kb_callback; int /*<<< orphan*/  kb_config; int /*<<< orphan*/  kb_type; scalar_t__ kb_data; } ;
typedef  TYPE_2__ keyboard_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_15__ {scalar_t__ ks_polling; int /*<<< orphan*/  ks_state; int /*<<< orphan*/  kbdc; } ;
typedef  TYPE_3__ atkbd_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KBDIO_KEYINPUT ; 
 int /*<<< orphan*/  KBD_FOUND_DEVICE (TYPE_2__*) ; 
 int /*<<< orphan*/  KBD_HAS_DEVICE (TYPE_2__*) ; 
 scalar_t__ KBD_IS_ACTIVE (TYPE_2__*) ; 
 scalar_t__ KBD_IS_BUSY (TYPE_2__*) ; 
 int /*<<< orphan*/  KDSETLED ; 
 int /*<<< orphan*/  KDSETREPEAT ; 
 int NOKEY ; 
 int /*<<< orphan*/  atkbd_ioctl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atkbd_read_char (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_keyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_typematic (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atkbd_intr(keyboard_t *kbd, void *arg)
{
	atkbd_state_t *state = (atkbd_state_t *)kbd->kb_data;
	int delay[2];
	int c;

	if (!KBD_HAS_DEVICE(kbd)) {
		/*
		 * The keyboard was not detected before;
		 * it must have been reconnected!
		 */
		init_keyboard(state->kbdc, &kbd->kb_type, kbd->kb_config);
		KBD_FOUND_DEVICE(kbd);
		atkbd_ioctl(kbd, KDSETLED, (caddr_t)&state->ks_state);
		set_typematic(kbd);
		delay[0] = kbd->kb_delay1;
		delay[1] = kbd->kb_delay2;
		atkbd_ioctl(kbd, KDSETREPEAT, (caddr_t)delay);
	}

	if (state->ks_polling)
		return 0;

	if (KBD_IS_ACTIVE(kbd) && KBD_IS_BUSY(kbd)) {
		/* let the callback function to process the input */
		(*kbd->kb_callback.kc_func)(kbd, KBDIO_KEYINPUT,
					    kbd->kb_callback.kc_arg);
	} else {
		/* read and discard the input; no one is waiting for input */
		do {
			c = atkbd_read_char(kbd, FALSE);
		} while (c != NOKEY);
	}
	return 0;
}