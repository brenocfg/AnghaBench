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
struct pvscsi_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINTF (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PVSCSI_CMD_RESET_BUS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pvscsi_process_cmp_ring (struct pvscsi_softc*) ; 
 int /*<<< orphan*/  pvscsi_write_cmd (struct pvscsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pvscsi_bus_reset(struct pvscsi_softc *sc)
{

	device_printf(sc->dev, "Bus Reset\n");

	pvscsi_write_cmd(sc, PVSCSI_CMD_RESET_BUS, NULL, 0);
	pvscsi_process_cmp_ring(sc);

	DEBUG_PRINTF(2, sc->dev, "bus reset done\n");
}