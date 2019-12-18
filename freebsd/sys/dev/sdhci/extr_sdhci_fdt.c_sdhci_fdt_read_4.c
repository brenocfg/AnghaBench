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
typedef  int /*<<< orphan*/  uint32_t ;
struct sdhci_slot {size_t num; } ;
struct sdhci_fdt_softc {scalar_t__ no_18v; int /*<<< orphan*/ * mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_CAN_VDD_180 ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sdhci_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
sdhci_fdt_read_4(device_t dev, struct sdhci_slot *slot, bus_size_t off)
{
	struct sdhci_fdt_softc *sc = device_get_softc(dev);
	uint32_t val32;

	val32 = bus_read_4(sc->mem_res[slot->num], off);
	if (off == SDHCI_CAPABILITIES && sc->no_18v)
		val32 &= ~SDHCI_CAN_VDD_180;

	return (val32);
}