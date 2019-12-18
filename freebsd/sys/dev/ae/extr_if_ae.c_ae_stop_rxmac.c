#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ae_softc_t ;

/* Variables and functions */
 scalar_t__ AE_DMAWRITE_EN ; 
 int /*<<< orphan*/  AE_DMAWRITE_REG ; 
 int AE_IDLE_DMAWRITE ; 
 int /*<<< orphan*/  AE_IDLE_REG ; 
 int AE_IDLE_RXMAC ; 
 int AE_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  AE_LOCK_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  AE_MAC_REG ; 
 int AE_MAC_RX_EN ; 
 scalar_t__ AE_READ_1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int AE_READ_4 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_WRITE_1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_WRITE_4 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ae_stop_rxmac(ae_softc_t *sc)
{
	uint32_t val;
	int i;

	AE_LOCK_ASSERT(sc);

	/*
	 * Stop Rx MAC engine.
	 */
	val = AE_READ_4(sc, AE_MAC_REG);
	if ((val & AE_MAC_RX_EN) != 0) {
		val &= ~AE_MAC_RX_EN;
		AE_WRITE_4(sc, AE_MAC_REG, val);
	}

	/*
	 * Stop Rx DMA engine.
	 */
	if (AE_READ_1(sc, AE_DMAWRITE_REG) == AE_DMAWRITE_EN)
		AE_WRITE_1(sc, AE_DMAWRITE_REG, 0);

	/*
	 * Wait for IDLE state.
	 */
	for (i = 0; i < AE_IDLE_TIMEOUT; i++) {
		val = AE_READ_4(sc, AE_IDLE_REG);
		if ((val & (AE_IDLE_RXMAC | AE_IDLE_DMAWRITE)) == 0)
			break;
		DELAY(100);
	}
	if (i == AE_IDLE_TIMEOUT)
		device_printf(sc->dev, "timed out while stopping Rx MAC.\n");
}