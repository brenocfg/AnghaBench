#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_4__ {int /*<<< orphan*/  kbdc; } ;
typedef  TYPE_2__ atkbd_state_t ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int /*<<< orphan*/  KBDC_DISABLE_KBD ; 
 int /*<<< orphan*/  KBDC_ENABLE_KBD ; 
 int KBD_AUX_CONTROL_BITS ; 
 int KBD_DISABLE_AUX_PORT ; 
 int KBD_DISABLE_KBD_INT ; 
 int KBD_ENABLE_KBD_PORT ; 
 int KBD_KBD_CONTROL_BITS ; 
 int KBD_TRANSLATION ; 
 int /*<<< orphan*/  send_kbd_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
atkbd_shutdown_final(void *v)
{
#ifdef __sparc64__
	keyboard_t *kbd = v;
	KBDC kbdc = ((atkbd_state_t *)kbd->kb_data)->kbdc;

	/*
	 * Turn off the translation in preparation for handing the keyboard
	 * over to the OFW as the OBP driver doesn't use translation and
	 * also doesn't disable it itself resulting in a broken keymap at
	 * the boot prompt. Also disable the aux port and the interrupts as
	 * the OBP driver doesn't use them, i.e. polls the keyboard. Not
	 * disabling the interrupts doesn't cause real problems but the
	 * responsiveness is a bit better when they are turned off.
	 */
	send_kbd_command(kbdc, KBDC_DISABLE_KBD);
	set_controller_command_byte(kbdc,
	    KBD_AUX_CONTROL_BITS | KBD_KBD_CONTROL_BITS | KBD_TRANSLATION,
	    KBD_DISABLE_AUX_PORT | KBD_DISABLE_KBD_INT | KBD_ENABLE_KBD_PORT);
	send_kbd_command(kbdc, KBDC_ENABLE_KBD);
#endif
}