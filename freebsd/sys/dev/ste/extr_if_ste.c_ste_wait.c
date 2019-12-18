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
struct ste_softc {int /*<<< orphan*/  ste_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  STE_DMACTL ; 
 int STE_DMACTL_DMA_HALTINPROG ; 
 int STE_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ste_wait(struct ste_softc *sc)
{
	int i;

	for (i = 0; i < STE_TIMEOUT; i++) {
		if (!(CSR_READ_4(sc, STE_DMACTL) & STE_DMACTL_DMA_HALTINPROG))
			break;
		DELAY(1);
	}

	if (i == STE_TIMEOUT)
		device_printf(sc->ste_dev, "command never completed!\n");
}