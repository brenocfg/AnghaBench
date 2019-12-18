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
 int FALSE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int TRUE ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
restore_controller(KBDC kbdc, int command_byte)
{
	empty_both_buffers(kbdc, 10);

	if (!set_controller_command_byte(kbdc, 0xff, command_byte)) {
		log(LOG_ERR, "psm: failed to restore the keyboard controller "
		    "command byte.\n");
		empty_both_buffers(kbdc, 10);
		return (FALSE);
	} else {
		empty_both_buffers(kbdc, 10);
		return (TRUE);
	}
}