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
struct ti_i2c_softc {int /*<<< orphan*/  clk_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_UNKNOWN ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int ti_i2c_reset (struct ti_i2c_softc*,int /*<<< orphan*/ ) ; 
 int ti_prcm_clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_i2c_activate(device_t dev)
{
	int err;
	struct ti_i2c_softc *sc;

	sc = (struct ti_i2c_softc*)device_get_softc(dev);

	/*
	 * 1. Enable the functional and interface clocks (see Section
	 * 23.1.5.1.1.1.1).
	 */
	err = ti_prcm_clk_enable(sc->clk_id);
	if (err)
		return (err);

	return (ti_i2c_reset(sc, IIC_UNKNOWN));
}