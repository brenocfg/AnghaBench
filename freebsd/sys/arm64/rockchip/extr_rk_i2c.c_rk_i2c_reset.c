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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct rk_i2c_softc {int /*<<< orphan*/  iicbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IICBUS_GET_FREQUENCY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK_I2C_CLKDIV ; 
 int /*<<< orphan*/  RK_I2C_CON ; 
 int /*<<< orphan*/  RK_I2C_LOCK (struct rk_i2c_softc*) ; 
 int /*<<< orphan*/  RK_I2C_UNLOCK (struct rk_i2c_softc*) ; 
 int /*<<< orphan*/  RK_I2C_WRITE (struct rk_i2c_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rk_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_i2c_get_clkdiv (struct rk_i2c_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rk_i2c_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	struct rk_i2c_softc *sc;
	uint32_t clkdiv;
	u_int busfreq;

	sc = device_get_softc(dev);

	busfreq = IICBUS_GET_FREQUENCY(sc->iicbus, speed);

	clkdiv = rk_i2c_get_clkdiv(sc, busfreq);

	RK_I2C_LOCK(sc);

	/* Set the clock divider */
	RK_I2C_WRITE(sc, RK_I2C_CLKDIV, clkdiv);

	/* Disable the module */
	RK_I2C_WRITE(sc, RK_I2C_CON, 0);

	RK_I2C_UNLOCK(sc);

	return (0);
}