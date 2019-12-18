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
struct rk_i2c_softc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK_I2C_CON ; 
 int /*<<< orphan*/  RK_I2C_CON_STOP ; 
 int /*<<< orphan*/  RK_I2C_IEN ; 
 int /*<<< orphan*/  RK_I2C_IEN_STOPIEN ; 
 int /*<<< orphan*/  RK_I2C_READ (struct rk_i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK_I2C_WRITE (struct rk_i2c_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_STOP ; 

__attribute__((used)) static void
rk_i2c_send_stop(struct rk_i2c_softc *sc)
{
	uint32_t reg;

	RK_I2C_WRITE(sc, RK_I2C_IEN, RK_I2C_IEN_STOPIEN);

	sc->state = STATE_STOP;

	reg = RK_I2C_READ(sc, RK_I2C_CON);
	reg |= RK_I2C_CON_STOP;
	RK_I2C_WRITE(sc, RK_I2C_CON, reg);
}