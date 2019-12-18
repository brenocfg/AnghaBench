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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINTF (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVSCSI_CMD_ADAPTER_RESET ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pvscsi_read_intr_status (struct pvscsi_softc*) ; 
 int /*<<< orphan*/  pvscsi_write_cmd (struct pvscsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pvscsi_adapter_reset(struct pvscsi_softc *sc)
{
	uint32_t val;

	device_printf(sc->dev, "Adapter Reset\n");

	pvscsi_write_cmd(sc, PVSCSI_CMD_ADAPTER_RESET, NULL, 0);
	val = pvscsi_read_intr_status(sc);

	DEBUG_PRINTF(2, sc->dev, "adapter reset done: %u\n", val);
}