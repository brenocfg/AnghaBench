#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int command_byte; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KBDC_DISABLE_KBD_PORT ; 
 int /*<<< orphan*/  KBDC_SET_COMMAND_BYTE ; 
 int KBD_DISABLE_KBD_PORT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int TRUE ; 
 int get_controller_command_byte (int /*<<< orphan*/ ) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  write_controller_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_controller_data (int /*<<< orphan*/ ,int) ; 

int
set_controller_command_byte(KBDC p, int mask, int command)
{
    if (get_controller_command_byte(p) == -1)
	return FALSE;

    command = (kbdcp(p)->command_byte & ~mask) | (command & mask);
    if (command & KBD_DISABLE_KBD_PORT) {
	if (!write_controller_command(p, KBDC_DISABLE_KBD_PORT))
	    return FALSE;
    }
    if (!write_controller_command(p, KBDC_SET_COMMAND_BYTE))
	return FALSE;
    if (!write_controller_data(p, command))
	return FALSE;
    kbdcp(p)->command_byte = command;

    if (verbose)
        log(LOG_DEBUG, "kbdc: new command byte:%04x (set_controller...)\n",
	    command);

    return TRUE;
}