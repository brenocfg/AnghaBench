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
typedef  int /*<<< orphan*/  uint8_t ;
struct powermac_nvram_softc {scalar_t__ sc_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ FLASH_TYPE_AMD ; 
 struct powermac_nvram_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int erase_bank_amd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int erase_bank_sm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
erase_bank(device_t dev, uint8_t *bank)
{
	struct powermac_nvram_softc *sc;

	sc = device_get_softc(dev);
	if (sc->sc_type == FLASH_TYPE_AMD)
		return (erase_bank_amd(dev, bank));
	else
		return (erase_bank_sm(dev, bank));
}