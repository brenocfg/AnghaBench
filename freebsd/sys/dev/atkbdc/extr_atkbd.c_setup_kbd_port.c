#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int KBD_DISABLE_KBD_INT ; 
 int KBD_DISABLE_KBD_PORT ; 
 int KBD_ENABLE_KBD_INT ; 
 int KBD_ENABLE_KBD_PORT ; 
 int /*<<< orphan*/  KBD_KBD_CONTROL_BITS ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
setup_kbd_port(KBDC kbdc, int port, int intr)
{
	if (!set_controller_command_byte(kbdc,
		KBD_KBD_CONTROL_BITS,
		((port) ? KBD_ENABLE_KBD_PORT : KBD_DISABLE_KBD_PORT)
		    | ((intr) ? KBD_ENABLE_KBD_INT : KBD_DISABLE_KBD_INT)))
		return 1;
	return 0;
}