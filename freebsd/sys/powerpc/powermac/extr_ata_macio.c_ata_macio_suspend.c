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
struct TYPE_2__ {int /*<<< orphan*/  attached; } ;
struct ata_dbdma_channel {int /*<<< orphan*/  dbdma; TYPE_1__ sc_ch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ata_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_save_state (int /*<<< orphan*/ ) ; 
 struct ata_dbdma_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_macio_suspend(device_t dev)
{
	struct ata_dbdma_channel *ch = device_get_softc(dev);
	int error;

	if (!ch->sc_ch.attached)
		return (0);

	error = ata_suspend(dev);
	dbdma_save_state(ch->dbdma);

	return (error);
}