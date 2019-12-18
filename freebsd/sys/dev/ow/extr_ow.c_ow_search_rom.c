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
struct ow_cmd {int rom_len; int /*<<< orphan*/ * rom_cmd; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  SEARCH_ROM ; 
 int /*<<< orphan*/  memset (struct ow_cmd*,int /*<<< orphan*/ ,int) ; 
 int ow_send_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ow_cmd*) ; 

__attribute__((used)) static int
ow_search_rom(device_t lldev, device_t dev)
{
	struct ow_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.rom_cmd[0] = SEARCH_ROM;
	cmd.rom_len = 1;
	return ow_send_command(lldev, dev, &cmd);
}