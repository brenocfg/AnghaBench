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
struct tegra124_car_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct tegra124_car_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int tegra124_hwreset_by_idx (struct tegra124_car_softc*,intptr_t,int) ; 

__attribute__((used)) static int
tegra124_car_hwreset_assert(device_t dev, intptr_t id, bool value)
{
	struct tegra124_car_softc *sc = device_get_softc(dev);

	return (tegra124_hwreset_by_idx(sc, id, value));
}