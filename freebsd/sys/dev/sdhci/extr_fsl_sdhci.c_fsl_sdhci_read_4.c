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
struct sdhci_slot {int dummy; } ;
struct fsl_sdhci_softc {int r1bfix_intmask; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int RD4 (struct fsl_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int SDHCI_CAN_DO_8BITBUS ; 
 int SDHCI_CAN_DO_SUSPEND ; 
 int SDHCI_CAN_VDD_180 ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int SDHCI_RETUNE_REQUEST ; 
 int SDHCI_STATE_DAT_MASK ; 
 struct fsl_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
fsl_sdhci_read_4(device_t dev, struct sdhci_slot *slot, bus_size_t off)
{
	struct fsl_sdhci_softc *sc = device_get_softc(dev);
	uint32_t val32, wrk32;

	val32 = RD4(sc, off);

	/*
	 * The hardware leaves the base clock frequency out of the capabilities
	 * register, but we filled it in by setting slot->max_clk at attach time
	 * rather than here, because we can't represent frequencies above 63MHz
	 * in an sdhci 2.0 capabliities register.  The timeout clock is the same
	 * as the active output sdclock; we indicate that with a quirk setting
	 * so don't populate the timeout frequency bits.
	 *
	 * XXX Turn off (for now) features the hardware can do but this driver
	 * doesn't yet handle (1.8v, suspend/resume, etc).
	 */
	if (off == SDHCI_CAPABILITIES) {
		val32 &= ~SDHCI_CAN_VDD_180;
		val32 &= ~SDHCI_CAN_DO_SUSPEND;
		val32 |= SDHCI_CAN_DO_8BITBUS;
		return (val32);
	}
	
	/*
	 * The hardware moves bits around in the present state register to make
	 * room for all 8 data line state bits.  To translate, mask out all the
	 * bits which are not in the same position in both registers (this also
	 * masks out some Freescale-specific bits in locations defined as
	 * reserved by sdhci), then shift the data line and retune request bits
	 * down to their standard locations.
	 */
	if (off == SDHCI_PRESENT_STATE) {
		wrk32 = val32;
		val32 &= 0x000F0F07;
		val32 |= (wrk32 >> 4) & SDHCI_STATE_DAT_MASK;
		val32 |= (wrk32 >> 9) & SDHCI_RETUNE_REQUEST;
		return (val32);
	}

	/*
	 * fsl_sdhci_intr() can synthesize a DATA_END interrupt following a
	 * command with an R1B response, mix it into the hardware status.
	 */
	if (off == SDHCI_INT_STATUS) {
		return (val32 | sc->r1bfix_intmask);
	}

	return val32;
}