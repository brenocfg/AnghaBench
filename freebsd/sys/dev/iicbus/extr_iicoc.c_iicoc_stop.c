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
struct iicoc_softc {int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OC_COMMAND_STOP ; 
 int /*<<< orphan*/  OC_I2C_CMD_REG ; 
 int /*<<< orphan*/  OC_STATUS_BUSY ; 
 struct iicoc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicoc_dev_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicoc_wait_on_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
iicoc_stop(device_t dev)
{
	int error = 0;
	struct iicoc_softc *sc;

	sc = device_get_softc(dev);
	mtx_lock(&sc->sc_mtx);
	iicoc_dev_write(dev, OC_I2C_CMD_REG, OC_COMMAND_STOP);
	iicoc_wait_on_status(dev, OC_STATUS_BUSY);  /* wait for idle */
	mtx_unlock(&sc->sc_mtx);
	return (error);

}