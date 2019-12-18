#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ata_port {int flags; int /*<<< orphan*/  port_no; TYPE_1__* host; int /*<<< orphan*/  tdev; } ;
struct ata_device {int /*<<< orphan*/  tdev; int /*<<< orphan*/  devno; TYPE_2__* link; } ;
struct TYPE_6__ {struct ata_device* dev; } ;
struct ata_acpi_hotplug_context {int /*<<< orphan*/  hp; TYPE_3__ data; } ;
struct acpi_device {scalar_t__ hp; } ;
struct TYPE_5__ {int /*<<< orphan*/  pmp; struct ata_port* ap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int ATA_FLAG_ACPI_SATA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NO_PORT_MULT ; 
 int /*<<< orphan*/  SATA_ADR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_initialize_hp_context (struct acpi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_preset_companion (int /*<<< orphan*/ *,struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_acpi_dev_notify_dock ; 
 int /*<<< orphan*/  ata_acpi_dev_uevent ; 
 struct ata_acpi_hotplug_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ libata_noacpi ; 
 int /*<<< orphan*/  sata_pmp_attached (struct ata_port*) ; 

void ata_acpi_bind_dev(struct ata_device *dev)
{
	struct ata_port *ap = dev->link->ap;
	struct acpi_device *port_companion = ACPI_COMPANION(&ap->tdev);
	struct acpi_device *host_companion = ACPI_COMPANION(ap->host->dev);
	struct acpi_device *parent, *adev;
	struct ata_acpi_hotplug_context *context;
	u64 adr;

	/*
	 * For both sata/pata devices, host companion device is required.
	 * For pata device, port companion device is also required.
	 */
	if (libata_noacpi || !host_companion ||
			(!(ap->flags & ATA_FLAG_ACPI_SATA) && !port_companion))
		return;

	if (ap->flags & ATA_FLAG_ACPI_SATA) {
		if (!sata_pmp_attached(ap))
			adr = SATA_ADR(ap->port_no, NO_PORT_MULT);
		else
			adr = SATA_ADR(ap->port_no, dev->link->pmp);
		parent = host_companion;
	} else {
		adr = dev->devno;
		parent = port_companion;
	}

	acpi_preset_companion(&dev->tdev, parent, adr);
	adev = ACPI_COMPANION(&dev->tdev);
	if (!adev || adev->hp)
		return;

	context = kzalloc(sizeof(*context), GFP_KERNEL);
	if (!context)
		return;

	context->data.dev = dev;
	acpi_initialize_hp_context(adev, &context->hp, ata_acpi_dev_notify_dock,
				   ata_acpi_dev_uevent);
}