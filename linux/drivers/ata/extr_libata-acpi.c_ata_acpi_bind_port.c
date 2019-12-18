#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ata_port {int flags; int /*<<< orphan*/  tdev; int /*<<< orphan*/  pflags; int /*<<< orphan*/  __acpi_init_gtm; int /*<<< orphan*/  port_no; TYPE_2__* host; } ;
struct TYPE_3__ {struct ata_port* ap; } ;
struct ata_acpi_hotplug_context {int /*<<< orphan*/  hp; TYPE_1__ data; } ;
struct acpi_device {scalar_t__ hp; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int ATA_FLAG_ACPI_SATA ; 
 int /*<<< orphan*/  ATA_PFLAG_INIT_GTM_VALID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_initialize_hp_context (struct acpi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_preset_companion (int /*<<< orphan*/ *,struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_acpi_ap_notify_dock ; 
 int /*<<< orphan*/  ata_acpi_ap_uevent ; 
 scalar_t__ ata_acpi_gtm (struct ata_port*,int /*<<< orphan*/ *) ; 
 struct ata_acpi_hotplug_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ libata_noacpi ; 

void ata_acpi_bind_port(struct ata_port *ap)
{
	struct acpi_device *host_companion = ACPI_COMPANION(ap->host->dev);
	struct acpi_device *adev;
	struct ata_acpi_hotplug_context *context;

	if (libata_noacpi || ap->flags & ATA_FLAG_ACPI_SATA || !host_companion)
		return;

	acpi_preset_companion(&ap->tdev, host_companion, ap->port_no);

	if (ata_acpi_gtm(ap, &ap->__acpi_init_gtm) == 0)
		ap->pflags |= ATA_PFLAG_INIT_GTM_VALID;

	adev = ACPI_COMPANION(&ap->tdev);
	if (!adev || adev->hp)
		return;

	context = kzalloc(sizeof(*context), GFP_KERNEL);
	if (!context)
		return;

	context->data.ap = ap;
	acpi_initialize_hp_context(adev, &context->hp, ata_acpi_ap_notify_dock,
				   ata_acpi_ap_uevent);
}