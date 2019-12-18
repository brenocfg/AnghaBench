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
struct ti_i2c_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_ENOADDR ; 
 int /*<<< orphan*/  TI_I2C_LOCK (struct ti_i2c_softc*) ; 
 int /*<<< orphan*/  TI_I2C_UNLOCK (struct ti_i2c_softc*) ; 
 struct ti_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ti_i2c_reset (struct ti_i2c_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_i2c_iicbus_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	struct ti_i2c_softc *sc;
	int err;

	sc = device_get_softc(dev);
	TI_I2C_LOCK(sc);
	err = ti_i2c_reset(sc, speed);
	TI_I2C_UNLOCK(sc);
	if (err)
		return (err);

	return (IIC_ENOADDR);
}