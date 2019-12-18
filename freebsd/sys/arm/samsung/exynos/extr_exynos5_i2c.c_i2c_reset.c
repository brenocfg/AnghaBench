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
struct i2c_softc {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int IIC_NOERR ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i2c_reset(device_t dev, u_char speed, u_char addr, u_char *oldadr)
{
	struct i2c_softc *sc;

	sc = device_get_softc(dev);

	DPRINTF("i2c reset\n");

	mtx_lock(&sc->mutex);

	/* TODO */

	mtx_unlock(&sc->mutex);

	return (IIC_NOERR);
}