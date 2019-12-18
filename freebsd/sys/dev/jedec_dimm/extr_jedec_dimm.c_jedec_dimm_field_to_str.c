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
typedef  int uint16_t ;
struct jedec_dimm_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  smbus; int /*<<< orphan*/  spd_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int JEDEC_DTI_PAGE ; 
 int JEDEC_LSA_PAGE_SET0 ; 
 int JEDEC_LSA_PAGE_SET1 ; 
 int JEDEC_SPD_PAGE_SIZE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int smbus_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int smbus_writeb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
jedec_dimm_field_to_str(struct jedec_dimm_softc *sc, char *dst, size_t dstsz,
    uint16_t offset, uint16_t len, bool ascii)
{
	uint8_t byte;
	int i;
	int rc;
	bool page_changed;

	/* Change to the proper page. Offsets [0, 255] are in page0; offsets
	 * [256, 512] are in page1.
	 *
	 * *The page must be reset to page0 before returning.*
	 *
	 * For the page-change operation, only the DTI and LSA matter; the
	 * offset and write-value are ignored, so use just 0.
	 *
	 * Mercifully, JEDEC defined the fields such that none of them cross
	 * pages, so we don't need to worry about that complication.
	 */
	if (offset < JEDEC_SPD_PAGE_SIZE) {
		page_changed = false;
	} else if (offset < (2 * JEDEC_SPD_PAGE_SIZE)) {
		page_changed = true;
		rc = smbus_writeb(sc->smbus,
		    (JEDEC_DTI_PAGE | JEDEC_LSA_PAGE_SET1), 0, 0);
		if (rc != 0) {
			device_printf(sc->dev,
			    "unable to change page for offset 0x%04x: %d\n",
			    offset, rc);
		}
		/* Adjust the offset to account for the page change. */
		offset -= JEDEC_SPD_PAGE_SIZE;
	} else {
		page_changed = false;
		rc = EINVAL;
		device_printf(sc->dev, "invalid offset 0x%04x\n", offset);
		goto out;
	}

	/* Sanity-check (adjusted) offset and length; everything must be within
	 * the same page.
	 */
	if (offset >= JEDEC_SPD_PAGE_SIZE) {
		rc = EINVAL;
		device_printf(sc->dev, "invalid offset 0x%04x\n", offset);
		goto out;
	}
	if ((offset + len) >= JEDEC_SPD_PAGE_SIZE) {
		rc = EINVAL;
		device_printf(sc->dev,
		    "(offset + len) would cross page (0x%04x + 0x%04x)\n",
		    offset, len);
		goto out;
	}

	/* Sanity-check the destination string length. If we're dealing with
	 * ASCII chars, then the destination must be at least the same length;
	 * otherwise, it must be *twice* the length, because each byte must
	 * be converted into two nybble characters.
	 *
	 * And, of course, there needs to be an extra byte for the terminator.
	 */
	if (ascii) {
		if (dstsz < (len + 1)) {
			rc = EINVAL;
			device_printf(sc->dev,
			    "destination too short (%u < %u)\n",
			    (uint16_t) dstsz, (len + 1));
			goto out;
		}
	} else {
		if (dstsz < ((2 * len) + 1)) {
			rc = EINVAL;
			device_printf(sc->dev,
			    "destination too short (%u < %u)\n",
			    (uint16_t) dstsz, ((2 * len) + 1));
			goto out;
		}
	}

	/* Read a byte at a time. */
	for (i = 0; i < len; i++) {
		rc = smbus_readb(sc->smbus, sc->spd_addr, (offset + i), &byte);
		if (rc != 0) {
			device_printf(sc->dev,
			    "failed to read byte at 0x%02x: %d\n",
			    (offset + i), rc);
			goto out;
		}
		if (ascii) {
			/* chars can be copied directly. */
			dst[i] = byte;
		} else {
			/* Raw bytes need to be converted to a two-byte hex
			 * string, plus the terminator.
			 */
			(void) snprintf(&dst[(2 * i)], 3, "%02x", byte);
		}
	}

	/* If we're dealing with ASCII, convert trailing spaces to NULs. */
	if (ascii) {
		for (i = dstsz; i > 0; i--) {
			if (dst[i] == ' ') {
				dst[i] = 0;
			} else if (dst[i] == 0) {
				continue;
			} else {
				break;
			}
		}
	}

out:
	if (page_changed) {
		int rc2;
		/* Switch back to page0 before returning. */
		rc2 = smbus_writeb(sc->smbus,
		    (JEDEC_DTI_PAGE | JEDEC_LSA_PAGE_SET0), 0, 0);
		if (rc2 != 0) {
			device_printf(sc->dev,
			    "unable to restore page for offset 0x%04x: %d\n",
			    offset, rc2);
		}
	}

	return (rc);
}