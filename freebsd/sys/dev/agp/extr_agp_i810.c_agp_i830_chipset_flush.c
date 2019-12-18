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
typedef  unsigned int uint32_t ;
struct agp_i810_softc {int /*<<< orphan*/ * sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I830_HIC ; 
 int /*<<< orphan*/  DELAY (int) ; 
 unsigned int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_cache () ; 

__attribute__((used)) static void
agp_i830_chipset_flush(device_t dev)
{
	struct agp_i810_softc *sc;
	uint32_t hic;
	int i;

	sc = device_get_softc(dev);
	pmap_invalidate_cache();
	hic = bus_read_4(sc->sc_res[0], AGP_I830_HIC);
	bus_write_4(sc->sc_res[0], AGP_I830_HIC, hic | (1U << 31));
	for (i = 0; i < 20000 /* 1 sec */; i++) {
		hic = bus_read_4(sc->sc_res[0], AGP_I830_HIC);
		if ((hic & (1U << 31)) == 0)
			break;
		DELAY(50);
	}
}