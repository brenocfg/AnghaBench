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
typedef  int /*<<< orphan*/  uint16_t ;
struct jedec_dimm_softc {int /*<<< orphan*/  tsod_addr; int /*<<< orphan*/  smbus; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int smbus_readw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jedec_dimm_readw_be(struct jedec_dimm_softc *sc, uint8_t reg, uint16_t *val)
{
	int rc;

	rc = smbus_readw(sc->smbus, sc->tsod_addr, reg, val);
	if (rc != 0) {
		goto out;
	}
	*val = be16toh(*val);

out:
	return (rc);
}