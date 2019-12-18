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
typedef  int /*<<< orphan*/  u_char ;
struct tegra_i2c_softc {int /*<<< orphan*/  iicbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IICBUS_GET_FREQUENCY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK (struct tegra_i2c_softc*) ; 
 int /*<<< orphan*/  UNLOCK (struct tegra_i2c_softc*) ; 
 struct tegra_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_i2c_setup_clk (struct tegra_i2c_softc*,int) ; 

__attribute__((used)) static int
tegra_i2c_iicbus_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	struct tegra_i2c_softc *sc;
	int busfreq;

	sc = device_get_softc(dev);
	busfreq = IICBUS_GET_FREQUENCY(sc->iicbus, speed);
	sc = device_get_softc(dev);
	LOCK(sc);
	tegra_i2c_setup_clk(sc, busfreq);
	UNLOCK(sc);
	return (0);
}