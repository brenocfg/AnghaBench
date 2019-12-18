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
 int /*<<< orphan*/  KBDC_FORCE_AUX_OUTPUT ; 
 int read_controller_data (int /*<<< orphan*/ ) ; 
 scalar_t__ write_controller_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_controller_data (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
set_aux_mux_state(KBDC p, int enabled)
{
	int command, version;

	if (write_controller_command(p, KBDC_FORCE_AUX_OUTPUT) == 0 ||
	    write_controller_data(p, 0xF0) == 0 ||
	    read_controller_data(p) != 0xF0)
		return (-1);

	if (write_controller_command(p, KBDC_FORCE_AUX_OUTPUT) == 0 ||
	    write_controller_data(p, 0x56) == 0 ||
	    read_controller_data(p) != 0x56)
		return (-1);

	command = enabled ? 0xa4 : 0xa5;
	if (write_controller_command(p, KBDC_FORCE_AUX_OUTPUT) == 0 ||
	    write_controller_data(p, command) == 0 ||
	    (version = read_controller_data(p)) == command)
		return (-1);

	return (version);
}