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
struct ale_softc {int /*<<< orphan*/  ale_dev; } ;

/* Variables and functions */
 int ALE_IDLE_STATUS ; 
 int ALE_MASTER_CFG ; 
 int ALE_RESET_TIMEOUT ; 
 int CSR_READ_4 (struct ale_softc*,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ale_softc*,int,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MASTER_RESET ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
ale_reset(struct ale_softc *sc)
{
	uint32_t reg;
	int i;

	/* Initialize PCIe module. From Linux. */
	CSR_WRITE_4(sc, 0x1008, CSR_READ_4(sc, 0x1008) | 0x8000);

	CSR_WRITE_4(sc, ALE_MASTER_CFG, MASTER_RESET);
	for (i = ALE_RESET_TIMEOUT; i > 0; i--) {
		DELAY(10);
		if ((CSR_READ_4(sc, ALE_MASTER_CFG) & MASTER_RESET) == 0)
			break;
	}
	if (i == 0)
		device_printf(sc->ale_dev, "master reset timeout!\n");

	for (i = ALE_RESET_TIMEOUT; i > 0; i--) {
		if ((reg = CSR_READ_4(sc, ALE_IDLE_STATUS)) == 0)
			break;
		DELAY(10);
	}

	if (i == 0)
		device_printf(sc->ale_dev, "reset timeout(0x%08x)!\n", reg);
}