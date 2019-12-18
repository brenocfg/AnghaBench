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
struct rk_i2c_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK_I2C_LOCK (struct rk_i2c_softc*) ; 
 int /*<<< orphan*/  RK_I2C_UNLOCK (struct rk_i2c_softc*) ; 
 int /*<<< orphan*/  rk_i2c_intr_locked (struct rk_i2c_softc*) ; 

__attribute__((used)) static void
rk_i2c_intr(void *arg)
{
	struct rk_i2c_softc *sc;

	sc = (struct rk_i2c_softc *)arg;

	RK_I2C_LOCK(sc);
	rk_i2c_intr_locked(sc);
	RK_I2C_UNLOCK(sc);
}