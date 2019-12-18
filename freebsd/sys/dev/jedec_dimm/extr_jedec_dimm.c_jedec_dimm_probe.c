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
typedef  int uint8_t ;
typedef  enum dram_type { ____Placeholder_dram_type } dram_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
#define  DRAM_TYPE_DDR3_SDRAM 129 
#define  DRAM_TYPE_DDR4_SDRAM 128 
 int ENXIO ; 
 int JEDEC_DTI_SPD ; 
 int /*<<< orphan*/  SPD_OFFSET_DRAM_TYPE ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int smbus_get_addr (int /*<<< orphan*/ ) ; 
 int smbus_readb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
jedec_dimm_probe(device_t dev)
{
	uint8_t addr;
	uint8_t byte;
	int rc;
	enum dram_type type;
	device_t smbus;

	smbus = device_get_parent(dev);
	addr = smbus_get_addr(dev);

	/* Don't bother if this isn't an SPD address, or if the LSBit is set. */
	if (((addr & 0xf0) != JEDEC_DTI_SPD) ||
	    ((addr & 0x01) != 0)) {
		device_printf(dev,
		    "invalid \"addr\" hint; address must start with \"0x%x\","
		    " and the least-significant bit must be 0\n",
		    JEDEC_DTI_SPD);
		rc = ENXIO;
		goto out;
	}

	/* Try to read the DRAM_TYPE from the SPD. */
	rc = smbus_readb(smbus, addr, SPD_OFFSET_DRAM_TYPE, &byte);
	if (rc != 0) {
		device_printf(dev, "failed to read dram_type\n");
		goto out;
	}

	/* This driver currently only supports DDR3 and DDR4 SPDs. */
	type = (enum dram_type) byte;
	switch (type) {
	case DRAM_TYPE_DDR3_SDRAM:
		rc = BUS_PROBE_DEFAULT;
		device_set_desc(dev, "DDR3 DIMM");
		break;
	case DRAM_TYPE_DDR4_SDRAM:
		rc = BUS_PROBE_DEFAULT;
		device_set_desc(dev, "DDR4 DIMM");
		break;
	default:
		rc = ENXIO;
		break;
	}

out:
	return (rc);
}