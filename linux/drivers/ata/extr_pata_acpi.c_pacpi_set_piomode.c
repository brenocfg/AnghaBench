#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; TYPE_1__* drive; } ;
struct pata_acpi {TYPE_2__ gtm; } ;
struct ata_timing {int /*<<< orphan*/  cycle; } ;
struct ata_port {struct pata_acpi* private_data; } ;
struct ata_device {int devno; int /*<<< orphan*/  pio_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  pio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_acpi_gtm (struct ata_port*,TYPE_2__*) ; 
 int /*<<< orphan*/  ata_acpi_stm (struct ata_port*,TYPE_2__*) ; 
 struct ata_timing* ata_timing_find_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pacpi_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	int unit = adev->devno;
	struct pata_acpi *acpi = ap->private_data;
	const struct ata_timing *t;

	if (!(acpi->gtm.flags & 0x10))
		unit = 0;

	/* Now stuff the nS values into the structure */
	t = ata_timing_find_mode(adev->pio_mode);
	acpi->gtm.drive[unit].pio = t->cycle;
	ata_acpi_stm(ap, &acpi->gtm);
	/* See what mode we actually got */
	ata_acpi_gtm(ap, &acpi->gtm);
}