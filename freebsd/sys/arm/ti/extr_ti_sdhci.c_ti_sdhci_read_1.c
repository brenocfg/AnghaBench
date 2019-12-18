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
struct ti_sdhci_softc {int dummy; } ;
struct sdhci_slot {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int RD4 (struct ti_sdhci_softc*,int) ; 
 struct ti_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
ti_sdhci_read_1(device_t dev, struct sdhci_slot *slot, bus_size_t off)
{
	struct ti_sdhci_softc *sc = device_get_softc(dev);

	return ((RD4(sc, off & ~3) >> (off & 3) * 8) & 0xff);
}