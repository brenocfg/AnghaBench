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
struct ow_cmd {int xpt_read_len; int /*<<< orphan*/ * xpt_read; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OW_FLAG_READ_BIT ; 
 int /*<<< orphan*/  READ_POWER_SUPPLY ; 
 int /*<<< orphan*/  own_command_wait (int /*<<< orphan*/ ,struct ow_cmd*) ; 
 int /*<<< orphan*/  own_self_command (int /*<<< orphan*/ ,struct ow_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ow_temp_read_power_supply(device_t dev, int *parasite)
{
	struct ow_cmd cmd;

	own_self_command(dev, &cmd, READ_POWER_SUPPLY);
	cmd.flags |= OW_FLAG_READ_BIT;
	cmd.xpt_read_len = 1;
	own_command_wait(dev, &cmd);
	*parasite = !cmd.xpt_read[0];	/* parasites pull bus low */

	return 0;
}