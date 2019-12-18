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
typedef  int /*<<< orphan*/  uint16_t ;
struct ti_i2c_softc {int /*<<< orphan*/  sc_error; int /*<<< orphan*/ * sc_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  I2C_REG_IRQENABLE_SET ; 
 int /*<<< orphan*/  I2C_REG_STATUS ; 
 int /*<<< orphan*/  TI_I2C_LOCK (struct ti_i2c_softc*) ; 
 int /*<<< orphan*/  TI_I2C_UNLOCK (struct ti_i2c_softc*) ; 
 int /*<<< orphan*/  ti_i2c_dbg (struct ti_i2c_softc*,char*) ; 
 int /*<<< orphan*/  ti_i2c_read_2 (struct ti_i2c_softc*,int /*<<< orphan*/ ) ; 
 int ti_i2c_transfer_intr (struct ti_i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct ti_i2c_softc*) ; 

__attribute__((used)) static void
ti_i2c_intr(void *arg)
{
	int done;
	struct ti_i2c_softc *sc;
	uint16_t events, status;

 	sc = (struct ti_i2c_softc *)arg;

	TI_I2C_LOCK(sc);

	status = ti_i2c_read_2(sc, I2C_REG_STATUS);
	if (status == 0) {
		TI_I2C_UNLOCK(sc);
		return;
	}

	/* Save enabled interrupts. */
	events = ti_i2c_read_2(sc, I2C_REG_IRQENABLE_SET);

	/* We only care about enabled interrupts. */
	status &= events;

	done = 0;

	if (sc->sc_buffer != NULL)
		done = ti_i2c_transfer_intr(sc, status);
	else {
		ti_i2c_dbg(sc, "Transfer interrupt without buffer\n");
		sc->sc_error = EINVAL;
		done = 1;
	}

	if (done)
		/* Wakeup the process that started the transaction. */
		wakeup(sc);

	TI_I2C_UNLOCK(sc);
}