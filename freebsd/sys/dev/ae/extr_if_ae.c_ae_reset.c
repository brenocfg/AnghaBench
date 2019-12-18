#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ * mem; } ;
typedef  TYPE_1__ ae_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IDLE_REG ; 
 int AE_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  AE_MASTER_REG ; 
 int AE_MASTER_SOFT_RESET ; 
 int AE_READ_4 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int AE_RESET_TIMEOUT ; 
 int /*<<< orphan*/  AE_WRITE_4 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ae_reset(ae_softc_t *sc)
{
	int i;

	/*
	 * Issue a soft reset.
	 */
	AE_WRITE_4(sc, AE_MASTER_REG, AE_MASTER_SOFT_RESET);
	bus_barrier(sc->mem[0], AE_MASTER_REG, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	
	/*
	 * Wait for reset to complete.
	 */
	for (i = 0; i < AE_RESET_TIMEOUT; i++) {
		if ((AE_READ_4(sc, AE_MASTER_REG) & AE_MASTER_SOFT_RESET) == 0)
			break;
		DELAY(10);
	}
	if (i == AE_RESET_TIMEOUT) {
		device_printf(sc->dev, "reset timeout.\n");
		return (ENXIO);
	}

	/*
	 * Wait for everything to enter idle state.
	 */
	for (i = 0; i < AE_IDLE_TIMEOUT; i++) {
		if (AE_READ_4(sc, AE_IDLE_REG) == 0)
			break;
		DELAY(100);
	}
	if (i == AE_IDLE_TIMEOUT) {
		device_printf(sc->dev, "could not enter idle state.\n");
		return (ENXIO);
	}
	return (0);
}