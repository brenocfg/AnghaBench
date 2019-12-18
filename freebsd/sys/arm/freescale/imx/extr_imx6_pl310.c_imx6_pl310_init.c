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
struct pl310_softc {int dummy; } ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  PL310_DATA_RAM_CTRL ; 
 int /*<<< orphan*/  PL310_POWER_CTRL ; 
 int /*<<< orphan*/  PL310_TAG_RAM_CTRL ; 
 int POWER_CTRL_ENABLE_GATING ; 
 int POWER_CTRL_ENABLE_STANDBY ; 
 int pl310_read4 (struct pl310_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl310_set_ram_latency (struct pl310_softc*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pl310_write4 (struct pl310_softc*,int /*<<< orphan*/ ,int) ; 

void
imx6_pl310_init(platform_t plat, struct pl310_softc *sc)
{
	uint32_t reg;

	/*
	 * Enable power saving modes:
	 *  - Dynamic Gating stops the clock when the controller is idle.
	 *  - Standby stops the clock when the cores are in WFI mode.
	 */
	reg = pl310_read4(sc, PL310_POWER_CTRL);
	reg |= POWER_CTRL_ENABLE_GATING | POWER_CTRL_ENABLE_STANDBY;
	pl310_write4(sc, PL310_POWER_CTRL, reg);

	pl310_set_ram_latency(sc, PL310_TAG_RAM_CTRL,  4, 2, 3);
	pl310_set_ram_latency(sc, PL310_DATA_RAM_CTRL, 4, 2, 3);
}