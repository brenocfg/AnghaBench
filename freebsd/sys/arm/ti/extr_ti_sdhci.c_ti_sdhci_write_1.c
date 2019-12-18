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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct ti_sdhci_softc {int dummy; } ;
struct sdhci_slot {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMCHS_CON ; 
 int MMCHS_CON_DW8 ; 
 int RD4 (struct ti_sdhci_softc*,int) ; 
 int SDHCI_CTRL_8BITBUS ; 
 int SDHCI_HOST_CONTROL ; 
 int /*<<< orphan*/  WR4 (struct ti_sdhci_softc*,int,int) ; 
 struct ti_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ti_mmchs_read_4 (struct ti_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_mmchs_write_4 (struct ti_sdhci_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ti_sdhci_write_1(device_t dev, struct sdhci_slot *slot, bus_size_t off, 
    uint8_t val)
{
	struct ti_sdhci_softc *sc = device_get_softc(dev);
	uint32_t val32;

#ifdef MMCCAM
	uint32_t newval32;
	if (off == SDHCI_HOST_CONTROL) {
		val32 = ti_mmchs_read_4(sc, MMCHS_CON);
		newval32  = val32;
		if (val & SDHCI_CTRL_8BITBUS) {
			device_printf(dev, "Custom-enabling 8-bit bus\n");
			newval32 |= MMCHS_CON_DW8;
		} else {
			device_printf(dev, "Custom-disabling 8-bit bus\n");
			newval32 &= ~MMCHS_CON_DW8;
		}
		if (newval32 != val32)
			ti_mmchs_write_4(sc, MMCHS_CON, newval32);
	}
#endif
	val32 = RD4(sc, off & ~3);
	val32 &= ~(0xff << (off & 3) * 8);
	val32 |= (val << (off & 3) * 8);

	WR4(sc, off & ~3, val32);
}