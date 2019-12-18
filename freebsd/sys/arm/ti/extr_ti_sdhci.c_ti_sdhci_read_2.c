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
struct ti_sdhci_softc {int cmd_and_mode; } ;
struct sdhci_slot {scalar_t__ version; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int MMCHS_SYSCTL_CLKD_MASK ; 
 int MMCHS_SYSCTL_CLKD_SHIFT ; 
 int RD4 (struct ti_sdhci_softc*,int) ; 
 int SDHCI_CLOCK_CONTROL ; 
 int SDHCI_COMMAND_FLAGS ; 
 int SDHCI_DIVIDER_HI_MASK ; 
 int SDHCI_DIVIDER_HI_SHIFT ; 
 int SDHCI_DIVIDER_MASK ; 
 int SDHCI_DIVIDER_MASK_LEN ; 
 int SDHCI_DIVIDER_SHIFT ; 
 scalar_t__ SDHCI_SPEC_300 ; 
 int SDHCI_TRANSFER_MODE ; 
 struct ti_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
ti_sdhci_read_2(device_t dev, struct sdhci_slot *slot, bus_size_t off)
{
	struct ti_sdhci_softc *sc = device_get_softc(dev);
	uint32_t clkdiv, val32;

	/*
	 * The MMCHS hardware has a non-standard interpretation of the sdclock
	 * divisor bits.  It uses the same bit positions as SDHCI 3.0 (15..6)
	 * but doesn't split them into low:high fields.  Instead they're a
	 * single number in the range 0..1023 and the number is exactly the
	 * clock divisor (with 0 and 1 both meaning divide by 1).  The SDHCI
	 * driver code expects a v2.0 or v3.0 divisor.  The shifting and masking
	 * here extracts the MMCHS representation from the hardware word, cleans
	 * those bits out, applies the 2N adjustment, and plugs the result into
	 * the bit positions for the 2.0 or 3.0 divisor in the returned register
	 * value. The ti_sdhci_write_2() routine performs the opposite
	 * transformation when the SDHCI driver writes to the register.
	 */
	if (off == SDHCI_CLOCK_CONTROL) {
		val32 = RD4(sc, SDHCI_CLOCK_CONTROL);
		clkdiv = ((val32 >> MMCHS_SYSCTL_CLKD_SHIFT) &
		    MMCHS_SYSCTL_CLKD_MASK) / 2;
		val32 &= ~(MMCHS_SYSCTL_CLKD_MASK << MMCHS_SYSCTL_CLKD_SHIFT);
		val32 |= (clkdiv & SDHCI_DIVIDER_MASK) << SDHCI_DIVIDER_SHIFT;
		if (slot->version >= SDHCI_SPEC_300)
			val32 |= ((clkdiv >> SDHCI_DIVIDER_MASK_LEN) &
			    SDHCI_DIVIDER_HI_MASK) << SDHCI_DIVIDER_HI_SHIFT;
		return (val32 & 0xffff);
	}

	/*
	 * Standard 32-bit handling of command and transfer mode.
	 */
	if (off == SDHCI_TRANSFER_MODE) {
		return (sc->cmd_and_mode >> 16);
	} else if (off == SDHCI_COMMAND_FLAGS) {
		return (sc->cmd_and_mode & 0x0000ffff);
	}

	return ((RD4(sc, off & ~3) >> (off & 3) * 8) & 0xffff);
}