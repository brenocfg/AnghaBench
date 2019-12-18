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
struct ata_device {int horkage; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ATA_HORKAGE_IVB ; 
 int ata_drive_40wire (int /*<<< orphan*/ ) ; 
 int ata_drive_40wire_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ata_is_40wire(struct ata_device *dev)
{
	if (dev->horkage & ATA_HORKAGE_IVB)
		return ata_drive_40wire_relaxed(dev->id);
	return ata_drive_40wire(dev->id);
}