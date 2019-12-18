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
typedef  int /*<<< orphan*/  uint8_t ;
struct jedec_dimm_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  smbus; int /*<<< orphan*/  spd_addr; } ;
typedef  enum dram_type { ____Placeholder_dram_type } dram_type ;

/* Variables and functions */
 int DRAM_TYPE_DDR4_SDRAM ; 
 int JEDEC_DTI_PAGE ; 
 int JEDEC_LSA_PAGE_SET0 ; 
 int JEDEC_LSA_PAGE_SET1 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  hexdump (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int smbus_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int smbus_writeb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jedec_dimm_dump(struct jedec_dimm_softc *sc, enum dram_type type)
{
	int i;
	int rc;
	bool page_changed;
	uint8_t bytes[512];

	page_changed = false;

	for (i = 0; i < 256; i++) {
		rc = smbus_readb(sc->smbus, sc->spd_addr, i, &bytes[i]);
		if (rc != 0) {
			device_printf(sc->dev,
			    "unable to read page0:0x%02x: %d\n", i, rc);
			goto out;
		}
	}

	/* The DDR4 SPD is 512 bytes, but SMBus only allows for 8-bit offsets.
	 * JEDEC gets around this by defining the "PAGE" DTI and LSAs.
	 */
	if (type == DRAM_TYPE_DDR4_SDRAM) {
		page_changed = true;
		rc = smbus_writeb(sc->smbus,
		    (JEDEC_DTI_PAGE | JEDEC_LSA_PAGE_SET1), 0, 0);
		if (rc != 0) {
			/* Some SPD devices (or SMBus controllers?) claim the
			 * page-change command failed when it actually
			 * succeeded. Log a message but soldier on.
			 */
			device_printf(sc->dev, "unable to change page: %d\n",
			    rc);
		}
		/* Add 256 to the store location, because we're in the second
		 * page.
		 */
		for (i = 0; i < 256; i++) {
			rc = smbus_readb(sc->smbus, sc->spd_addr, i,
			    &bytes[256 + i]);
			if (rc != 0) {
				device_printf(sc->dev,
				    "unable to read page1:0x%02x: %d\n", i, rc);
				goto out;
			}
		}
	}

	/* Display the data in a nice hexdump format, with byte offsets. */
	hexdump(bytes, (page_changed ? 512 : 256), NULL, 0);

out:
	if (page_changed) {
		int rc2;
		/* Switch back to page0 before returning. */
		rc2 = smbus_writeb(sc->smbus,
		    (JEDEC_DTI_PAGE | JEDEC_LSA_PAGE_SET0), 0, 0);
		if (rc2 != 0) {
			device_printf(sc->dev, "unable to restore page: %d\n",
			    rc2);
		}
	}
	return (rc);
}