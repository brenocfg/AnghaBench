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
typedef  scalar_t__ uint32_t ;
struct bwi_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 scalar_t__ BWI_PCIM_REGWIN (int) ; 
 int /*<<< orphan*/  BWI_PCIR_SEL_REGWIN ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int RETRY_MAX ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
bwi_regwin_select(struct bwi_softc *sc, int id)
{
	uint32_t win = BWI_PCIM_REGWIN(id);
	int i;

#define RETRY_MAX	50
	for (i = 0; i < RETRY_MAX; ++i) {
		pci_write_config(sc->sc_dev, BWI_PCIR_SEL_REGWIN, win, 4);
		if (pci_read_config(sc->sc_dev, BWI_PCIR_SEL_REGWIN, 4) == win)
			return 0;
		DELAY(10);
	}
#undef RETRY_MAX

	return ENXIO;
}