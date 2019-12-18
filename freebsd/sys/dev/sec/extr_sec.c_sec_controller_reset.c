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
struct sec_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SEC_MCR ; 
 int SEC_MCR_SWR ; 
 int SEC_READ (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int SEC_TIMEOUT ; 
 int /*<<< orphan*/  SEC_WRITE (struct sec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
sec_controller_reset(struct sec_softc *sc)
{
	int timeout = SEC_TIMEOUT;

	/* Reset Controller */
	SEC_WRITE(sc, SEC_MCR, SEC_MCR_SWR);

	while (SEC_READ(sc, SEC_MCR) & SEC_MCR_SWR) {
		DELAY(1000);
		timeout -= 1000;

		if (timeout < 0) {
			device_printf(sc->sc_dev, "timeout while waiting for "
			    "device reset!\n");
			return (ETIMEDOUT);
		}
	}

	return (0);
}