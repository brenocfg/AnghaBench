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
typedef  int uint32_t ;
struct ata_channel {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_SSTATUS ; 
 scalar_t__ ata_sata_scr_read (struct ata_channel*,int,int /*<<< orphan*/ ,int*) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_intel_sata_getrev(device_t dev, int target)
{
	struct ata_channel *ch = device_get_softc(dev);
	uint32_t status;

	if (ata_sata_scr_read(ch, target, ATA_SSTATUS, &status) == 0)
		return ((status & 0x0f0) >> 4);
	return (0xff);
}