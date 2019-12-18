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
typedef  int /*<<< orphan*/  uint32_t ;
struct pvscsi_softc {int /*<<< orphan*/  dev; } ;
struct pvscsi_cmd_desc_reset_device {int /*<<< orphan*/  target; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINTF (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PVSCSI_CMD_RESET_DEVICE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pvscsi_cmd_desc_reset_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvscsi_process_cmp_ring (struct pvscsi_softc*) ; 
 int /*<<< orphan*/  pvscsi_write_cmd (struct pvscsi_softc*,int /*<<< orphan*/ ,struct pvscsi_cmd_desc_reset_device*,int) ; 

__attribute__((used)) static void
pvscsi_device_reset(struct pvscsi_softc *sc, uint32_t target)
{
	struct pvscsi_cmd_desc_reset_device cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.target = target;

	device_printf(sc->dev, "Device reset for target %u\n", target);

	pvscsi_write_cmd(sc, PVSCSI_CMD_RESET_DEVICE, &cmd, sizeof cmd);
	pvscsi_process_cmp_ring(sc);

	DEBUG_PRINTF(2, sc->dev, "device reset done\n");
}