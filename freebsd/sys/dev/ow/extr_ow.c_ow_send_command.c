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
struct ow_timing {int dummy; } ;
struct ow_cmd {int rom_len; int rom_read_len; int* rom_read; int xpt_len; int flags; int* xpt_read; int xpt_read_len; int /*<<< orphan*/ * xpt_cmd; int /*<<< orphan*/ * rom_cmd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  OWLL_READ_DATA (int /*<<< orphan*/ ,struct ow_timing*,int*) ; 
 int /*<<< orphan*/  OWLL_RESET_AND_PRESENCE (int /*<<< orphan*/ ,struct ow_timing*,int*) ; 
 int OW_FLAG_OVERDRIVE ; 
 int OW_FLAG_READ_BIT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ow_read_byte (int /*<<< orphan*/ ,struct ow_timing*,int*) ; 
 int /*<<< orphan*/  ow_send_byte (int /*<<< orphan*/ ,struct ow_timing*,int /*<<< orphan*/ ) ; 
 struct ow_timing timing_overdrive ; 
 struct ow_timing timing_regular ; 

__attribute__((used)) static int
ow_send_command(device_t ndev, device_t pdev, struct ow_cmd *cmd)
{
	int present, i, bit, tries;
	device_t lldev;
	struct ow_timing *t;

	lldev = device_get_parent(ndev);

	/*
	 * Retry the reset a couple of times before giving up.
	 */
	tries = 4;
	do {
		OWLL_RESET_AND_PRESENCE(lldev, &timing_regular, &present);
		if (present == 1)
			device_printf(ndev, "Reset said no device on bus?.\n");
	} while (present == 1 && tries-- > 0);
	if (present == 1) {
		device_printf(ndev, "Reset said the device wasn't there.\n");
		return ENOENT;		/* No devices acked the RESET */
	}
	if (present == -1) {
		device_printf(ndev, "Reset discovered bus wired wrong.\n");
		return ENOENT;
	}

	for (i = 0; i < cmd->rom_len; i++)
		ow_send_byte(lldev, &timing_regular, cmd->rom_cmd[i]);
	for (i = 0; i < cmd->rom_read_len; i++)
		ow_read_byte(lldev, &timing_regular, cmd->rom_read + i);
	if (cmd->xpt_len) {
		/*
		 * Per AN937, the reset pulse and ROM level are always
		 * done with the regular timings. Certain ROM commands
		 * put the device into overdrive mode for the remainder
		 * of the data transfer, which is why we have to pass the
		 * timings here. Commands that need to be handled like this
		 * are expected to be flagged by the client.
		 */
		t = (cmd->flags & OW_FLAG_OVERDRIVE) ?
		    &timing_overdrive : &timing_regular;
		for (i = 0; i < cmd->xpt_len; i++)
			ow_send_byte(lldev, t, cmd->xpt_cmd[i]);
		if (cmd->flags & OW_FLAG_READ_BIT) {
			memset(cmd->xpt_read, 0, (cmd->xpt_read_len + 7) / 8);
			for (i = 0; i < cmd->xpt_read_len; i++) {
				OWLL_READ_DATA(lldev, t, &bit);
				cmd->xpt_read[i / 8] |= bit << (i % 8);
			}
		} else {
			for (i = 0; i < cmd->xpt_read_len; i++)
				ow_read_byte(lldev, t, cmd->xpt_read + i);
		}
	}
	return 0;
}