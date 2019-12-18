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
struct ata_channel {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_NO_SLAVE ; 
 int /*<<< orphan*/  ATA_SCONTROL ; 
 int ATA_SC_IPM_DIS_PARTIAL ; 
 int ATA_SC_IPM_DIS_SLUMBER ; 
 int ATA_SC_IPM_MASK ; 
 int /*<<< orphan*/  ata_intel_sata_sidpr_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ata_intel_sata_sidpr_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
ata_intel_sata_sidpr_test(device_t dev)
{
	struct ata_channel *ch = device_get_softc(dev);
	int port;
	uint32_t val;

	port = (ch->flags & ATA_NO_SLAVE) ? 0 : 1;
	for (; port >= 0; port--) {
		ata_intel_sata_sidpr_read(dev, port, ATA_SCONTROL, &val);
		if ((val & ATA_SC_IPM_MASK) ==
		    (ATA_SC_IPM_DIS_PARTIAL | ATA_SC_IPM_DIS_SLUMBER))
			return (1);
		val |= ATA_SC_IPM_DIS_PARTIAL | ATA_SC_IPM_DIS_SLUMBER;
		ata_intel_sata_sidpr_write(dev, port, ATA_SCONTROL, val);
		ata_intel_sata_sidpr_read(dev, port, ATA_SCONTROL, &val);
		if ((val & ATA_SC_IPM_MASK) ==
		    (ATA_SC_IPM_DIS_PARTIAL | ATA_SC_IPM_DIS_SLUMBER))
			return (1);
	}
	if (bootverbose)
		device_printf(dev,
		    "SControl registers are not functional: %08x\n", val);
	return (0);
}