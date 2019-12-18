#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int pages; TYPE_1__* page; } ;
struct upgt_softc {int /*<<< orphan*/  sc_dev; TYPE_2__ sc_memory; } ;
struct TYPE_3__ {scalar_t__ addr; scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
upgt_mem_free(struct upgt_softc *sc, uint32_t addr)
{
	int i;

	for (i = 0; i < sc->sc_memory.pages; i++) {
		if (sc->sc_memory.page[i].addr == addr) {
			sc->sc_memory.page[i].used = 0;
			return;
		}
	}

	device_printf(sc->sc_dev,
	    "could not free memory address 0x%08x\n", addr);
}