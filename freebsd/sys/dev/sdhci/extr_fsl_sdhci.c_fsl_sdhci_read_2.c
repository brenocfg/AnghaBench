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
typedef  int uint16_t ;
struct sdhci_slot {int dummy; } ;
struct fsl_sdhci_softc {scalar_t__ hwtype; int cmd_and_mode; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 scalar_t__ HWTYPE_ESDHC ; 
 scalar_t__ HWTYPE_USDHC ; 
 int RD4 (struct fsl_sdhci_softc*,int) ; 
 int SDHCI_CLOCK_CONTROL ; 
 int SDHCI_COMMAND_FLAGS ; 
 int SDHCI_HOST_VERSION ; 
 int SDHCI_INT_STATUS ; 
 int SDHCI_SIGNAL_ENABLE ; 
 int SDHCI_SLOT_INT_STATUS ; 
 int SDHCI_SPEC_300 ; 
 int SDHCI_SPEC_VER_SHIFT ; 
 int SDHCI_TRANSFER_MODE ; 
 int USDHC_MIX_CONTROL ; 
 struct fsl_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int fsl_sdhc_get_clock (struct fsl_sdhci_softc*) ; 

__attribute__((used)) static uint16_t
fsl_sdhci_read_2(device_t dev, struct sdhci_slot *slot, bus_size_t off)
{
	struct fsl_sdhci_softc *sc = device_get_softc(dev);
	uint32_t val32;

	if (sc->hwtype == HWTYPE_USDHC) {
		/*
		 * The USDHC hardware has nothing in the version register, but
		 * it's v3 compatible with all our translation code.
		 */
		if (off == SDHCI_HOST_VERSION) {
			return (SDHCI_SPEC_300 << SDHCI_SPEC_VER_SHIFT);
		}
		/*
		 * The USDHC hardware moved the transfer mode bits to the mixed
		 * control register, fetch them from there.
		 */
		if (off == SDHCI_TRANSFER_MODE)
			return (RD4(sc, USDHC_MIX_CONTROL) & 0x37);

	} else if (sc->hwtype == HWTYPE_ESDHC) {

		/*
		 * The ESDHC hardware has the typical 32-bit combined "command
		 * and mode" register that we have to cache so that command
		 * isn't written until after mode.  On a read, just retrieve the
		 * cached values last written.
		 */
		if (off == SDHCI_TRANSFER_MODE) {
			return (sc->cmd_and_mode & 0x0000ffff);
		} else if (off == SDHCI_COMMAND_FLAGS) {
			return (sc->cmd_and_mode >> 16);
		}
	}

	/*
	 * This hardware only manages one slot.  Synthesize a slot interrupt
	 * status register... if there are any enabled interrupts active they
	 * must be coming from our one and only slot.
	 */
	if (off == SDHCI_SLOT_INT_STATUS) {
		val32  = RD4(sc, SDHCI_INT_STATUS);
		val32 &= RD4(sc, SDHCI_SIGNAL_ENABLE);
		return (val32 ? 1 : 0);
	}

	/*
	 * Clock bits are scattered into various registers which differ by
	 * hardware type, complex enough to have their own function.
	 */
	if (off == SDHCI_CLOCK_CONTROL) {
		return (fsl_sdhc_get_clock(sc));
	}

	return ((RD4(sc, off & ~3) >> (off & 3) * 8) & 0xffff);
}