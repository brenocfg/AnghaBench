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
typedef  int u_char ;
struct i2c_softc {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  I2C_IBCR ; 
 int /*<<< orphan*/  I2C_IBFD ; 
 int IBCR_MDIS ; 
#define  IIC_FAST 131 
#define  IIC_FASTEST 130 
 int IIC_NOERR ; 
#define  IIC_SLOW 129 
#define  IIC_UNKNOWN 128 
 int /*<<< orphan*/  WRITE1 (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vf_i2c_dbg (struct i2c_softc*,char*) ; 

__attribute__((used)) static int
i2c_reset(device_t dev, u_char speed, u_char addr, u_char *oldadr)
{
	struct i2c_softc *sc;

	sc = device_get_softc(dev);

	vf_i2c_dbg(sc, "i2c reset\n");

	switch (speed) {
	case IIC_FAST:
	case IIC_SLOW:
	case IIC_UNKNOWN:
	case IIC_FASTEST:
	default:
		break;
	}

	mtx_lock(&sc->mutex);
	WRITE1(sc, I2C_IBCR, IBCR_MDIS);

	DELAY(1000);

	WRITE1(sc, I2C_IBFD, 20);
	WRITE1(sc, I2C_IBCR, 0x0); /* Enable i2c */

	DELAY(1000);

	mtx_unlock(&sc->mutex);

	return (IIC_NOERR);
}