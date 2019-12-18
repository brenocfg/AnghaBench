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
struct ata_device {int /*<<< orphan*/  ering; int /*<<< orphan*/  class; TYPE_1__* link; } ;
struct TYPE_2__ {int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int ATA_DNXFER_FORCE_PIO0 ; 
 int ATA_DNXFER_QUIET ; 
 int /*<<< orphan*/  ata_acpi_on_disable (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_enabled (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*) ; 
 int /*<<< orphan*/  ata_down_xfermask_limit (struct ata_device*,int) ; 
 int /*<<< orphan*/  ata_ering_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ ata_msg_drv (int /*<<< orphan*/ ) ; 

void ata_dev_disable(struct ata_device *dev)
{
	if (!ata_dev_enabled(dev))
		return;

	if (ata_msg_drv(dev->link->ap))
		ata_dev_warn(dev, "disabled\n");
	ata_acpi_on_disable(dev);
	ata_down_xfermask_limit(dev, ATA_DNXFER_FORCE_PIO0 | ATA_DNXFER_QUIET);
	dev->class++;

	/* From now till the next successful probe, ering is used to
	 * track probe failures.  Clear accumulated device error info.
	 */
	ata_ering_clear(&dev->ering);
}