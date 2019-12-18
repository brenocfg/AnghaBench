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
struct are_softc {int /*<<< orphan*/  are_dev; } ;

/* Variables and functions */
 int BUSMODE_SWR ; 
 int /*<<< orphan*/  CSR_BUSMODE ; 
 int CSR_READ_4 (struct are_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct are_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
are_reset(struct are_softc *sc)
{
	int		i;

	CSR_WRITE_4(sc, CSR_BUSMODE, BUSMODE_SWR);

	/*
	 * The chip doesn't take itself out of reset automatically.
	 * We need to do so after 2us.
	 */
	DELAY(10);
	CSR_WRITE_4(sc, CSR_BUSMODE, 0);

	for (i = 0; i < 1000; i++) {
		/*
		 * Wait a bit for the reset to complete before peeking
		 * at the chip again.
		 */
		DELAY(10);
		if ((CSR_READ_4(sc, CSR_BUSMODE) & BUSMODE_SWR) == 0)
			break;
	}

	if (CSR_READ_4(sc, CSR_BUSMODE) & BUSMODE_SWR)
		device_printf(sc->are_dev, "reset time out\n");

	DELAY(1000);
}