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
struct pata_acpi {unsigned long* mask; } ;
struct ata_device {size_t devno; TYPE_2__* link; } ;
struct TYPE_4__ {TYPE_1__* ap; } ;
struct TYPE_3__ {struct pata_acpi* private_data; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long pacpi_mode_filter(struct ata_device *adev, unsigned long mask)
{
	struct pata_acpi *acpi = adev->link->ap->private_data;
	return mask & acpi->mask[adev->devno];
}