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
struct mmc_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_timing_normal ; 
 int /*<<< orphan*/  bus_width_1 ; 
 int /*<<< orphan*/  cs_dontcare ; 
 int /*<<< orphan*/  mmcbr_set_bus_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_bus_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_chip_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_power_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_timing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_update_ios (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opendrain ; 
 int /*<<< orphan*/  power_off ; 

__attribute__((used)) static void
mmc_power_down(struct mmc_softc *sc)
{
	device_t dev = sc->dev;

	mmcbr_set_bus_mode(dev, opendrain);
	mmcbr_set_chip_select(dev, cs_dontcare);
	mmcbr_set_bus_width(dev, bus_width_1);
	mmcbr_set_power_mode(dev, power_off);
	mmcbr_set_clock(dev, 0);
	mmcbr_set_timing(dev, bus_timing_normal);
	mmcbr_update_ios(dev);
}