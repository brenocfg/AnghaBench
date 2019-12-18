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
typedef  int u_int32_t ;
struct bfe_softc {int /*<<< orphan*/  bfe_dev; } ;

/* Variables and functions */
 int BMCR_RESET ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  bfe_readphy (struct bfe_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bfe_writephy (struct bfe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bfe_resetphy(struct bfe_softc *sc)
{
	u_int32_t val;

	bfe_writephy(sc, 0, BMCR_RESET);
	DELAY(100);
	bfe_readphy(sc, 0, &val);
	if (val & BMCR_RESET) {
		device_printf(sc->bfe_dev, "PHY Reset would not complete.\n");
		return (ENXIO);
	}
	return (0);
}