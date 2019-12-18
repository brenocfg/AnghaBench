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
struct wpi_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WPI_GP_CNTRL ; 
 int WPI_GP_CNTRL_MAC_ACCESS_ENA ; 
 int /*<<< orphan*/  WPI_GP_CNTRL_MAC_ACCESS_REQ ; 
 int WPI_GP_CNTRL_SLEEP ; 
 int WPI_READ (struct wpi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPI_SETBITS (struct wpi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
wpi_nic_lock(struct wpi_softc *sc)
{
	int ntries;

	/* Request exclusive access to NIC. */
	WPI_SETBITS(sc, WPI_GP_CNTRL, WPI_GP_CNTRL_MAC_ACCESS_REQ);

	/* Spin until we actually get the lock. */
	for (ntries = 0; ntries < 1000; ntries++) {
		if ((WPI_READ(sc, WPI_GP_CNTRL) &
		    (WPI_GP_CNTRL_MAC_ACCESS_ENA | WPI_GP_CNTRL_SLEEP)) ==
		    WPI_GP_CNTRL_MAC_ACCESS_ENA)
			return 0;
		DELAY(10);
	}

	device_printf(sc->sc_dev, "could not lock memory\n");

	return ETIMEDOUT;
}