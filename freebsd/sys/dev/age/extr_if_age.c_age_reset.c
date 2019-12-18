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
typedef  int uint32_t ;
struct age_softc {int /*<<< orphan*/  age_dev; } ;

/* Variables and functions */
 int AGE_IDLE_STATUS ; 
 int AGE_MASTER_CFG ; 
 int AGE_RESET_TIMEOUT ; 
 int CSR_READ_4 (struct age_softc*,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct age_softc*,int,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MASTER_RESET ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
age_reset(struct age_softc *sc)
{
	uint32_t reg;
	int i;

	CSR_WRITE_4(sc, AGE_MASTER_CFG, MASTER_RESET);
	CSR_READ_4(sc, AGE_MASTER_CFG);
	DELAY(1000);
	for (i = AGE_RESET_TIMEOUT; i > 0; i--) {
		if ((reg = CSR_READ_4(sc, AGE_IDLE_STATUS)) == 0)
			break;
		DELAY(10);
	}

	if (i == 0)
		device_printf(sc->age_dev, "reset timeout(0x%08x)!\n", reg);
	/* Initialize PCIe module. From Linux. */
	CSR_WRITE_4(sc, 0x12FC, 0x6500);
	CSR_WRITE_4(sc, 0x1008, CSR_READ_4(sc, 0x1008) | 0x8000);
}