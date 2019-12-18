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
struct tegra124_car_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKDEV_DEVICE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLKDEV_DEVICE_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLKDEV_MODIFY_4 (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  CLKDEV_READ_4 (int /*<<< orphan*/ ,int,int*) ; 
 int get_reset_reg (intptr_t) ; 

int
tegra124_hwreset_by_idx(struct tegra124_car_softc *sc, intptr_t idx, bool reset)
{
	uint32_t reg, mask, reset_reg;

	mask = 1 << (idx % 32);
	reset_reg = get_reset_reg(idx);

	CLKDEV_DEVICE_LOCK(sc->dev);
	CLKDEV_MODIFY_4(sc->dev, reset_reg, mask, reset ? mask : 0);
	CLKDEV_READ_4(sc->dev, reset_reg, &reg);
	CLKDEV_DEVICE_UNLOCK(sc->dev);

	return(0);
}