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
struct rt2860_softc {int /*<<< orphan*/  sc_dev; } ;
struct firmware {int /*<<< orphan*/  datasize; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  RAL_BARRIER_READ_WRITE (struct rt2860_softc*) ; 
 int /*<<< orphan*/  RAL_BARRIER_WRITE (struct rt2860_softc*) ; 
 int /*<<< orphan*/  RAL_LOCK (struct rt2860_softc*) ; 
 int /*<<< orphan*/  RAL_LOCK_ASSERT (struct rt2860_softc*) ; 
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct rt2860_softc*) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE_REGION_1 (struct rt2860_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2860_FW_BASE ; 
 int /*<<< orphan*/  RT2860_H2M_BBPAGENT ; 
 int /*<<< orphan*/  RT2860_H2M_MAILBOX ; 
 int /*<<< orphan*/  RT2860_HST_PM_SEL ; 
 int RT2860_MCU_READY ; 
 int /*<<< orphan*/  RT2860_MCU_RESET ; 
 int /*<<< orphan*/  RT2860_SYS_CTRL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct firmware* firmware_get (char*) ; 
 int /*<<< orphan*/  firmware_put (struct firmware const*,int /*<<< orphan*/ ) ; 

int
rt2860_load_microcode(struct rt2860_softc *sc)
{
	const struct firmware *fp;
	int ntries, error;

	RAL_LOCK_ASSERT(sc);

	RAL_UNLOCK(sc);
	fp = firmware_get("rt2860fw");
	RAL_LOCK(sc);
	if (fp == NULL) {
		device_printf(sc->sc_dev,
		    "unable to receive rt2860fw firmware image\n");
		return EINVAL;
	}

	/* set "host program ram write selection" bit */
	RAL_WRITE(sc, RT2860_SYS_CTRL, RT2860_HST_PM_SEL);
	/* write microcode image */
	RAL_WRITE_REGION_1(sc, RT2860_FW_BASE, fp->data, fp->datasize);
	/* kick microcontroller unit */
	RAL_WRITE(sc, RT2860_SYS_CTRL, 0);
	RAL_BARRIER_WRITE(sc);
	RAL_WRITE(sc, RT2860_SYS_CTRL, RT2860_MCU_RESET);

	RAL_WRITE(sc, RT2860_H2M_BBPAGENT, 0);
	RAL_WRITE(sc, RT2860_H2M_MAILBOX, 0);

	/* wait until microcontroller is ready */
	RAL_BARRIER_READ_WRITE(sc);
	for (ntries = 0; ntries < 1000; ntries++) {
		if (RAL_READ(sc, RT2860_SYS_CTRL) & RT2860_MCU_READY)
			break;
		DELAY(1000);
	}
	if (ntries == 1000) {
		device_printf(sc->sc_dev,
		    "timeout waiting for MCU to initialize\n");
		error = ETIMEDOUT;
	} else
		error = 0;

	firmware_put(fp, FIRMWARE_UNLOAD);
	return error;
}