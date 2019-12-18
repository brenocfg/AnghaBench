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
typedef  int /*<<< orphan*/  uint16_t ;
struct sdhci_slot {size_t num; } ;
struct sdhci_fdt_softc {int /*<<< orphan*/ * mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sdhci_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdhci_fdt_write_2(device_t dev, struct sdhci_slot *slot, bus_size_t off,
    uint16_t val)
{
	struct sdhci_fdt_softc *sc = device_get_softc(dev);

	bus_write_2(sc->mem_res[slot->num], off, val);
}