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
struct TYPE_4__ {int pages; TYPE_1__* page; } ;
struct upgt_softc {scalar_t__ sc_memaddr_frame_start; scalar_t__ sc_memaddr_frame_end; TYPE_2__ sc_memory; } ;
struct TYPE_3__ {scalar_t__ addr; scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct upgt_softc*,int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ MCLBYTES ; 
 int /*<<< orphan*/  UPGT_DEBUG_FW ; 
 int UPGT_MEMORY_MAX_PAGES ; 

__attribute__((used)) static int
upgt_mem_init(struct upgt_softc *sc)
{
	int i;

	for (i = 0; i < UPGT_MEMORY_MAX_PAGES; i++) {
		sc->sc_memory.page[i].used = 0;

		if (i == 0) {
			/*
			 * The first memory page is always reserved for
			 * command data.
			 */
			sc->sc_memory.page[i].addr =
			    sc->sc_memaddr_frame_start + MCLBYTES;
		} else {
			sc->sc_memory.page[i].addr =
			    sc->sc_memory.page[i - 1].addr + MCLBYTES;
		}

		if (sc->sc_memory.page[i].addr + MCLBYTES >=
		    sc->sc_memaddr_frame_end)
			break;

		DPRINTF(sc, UPGT_DEBUG_FW, "memory address page %d=0x%08x\n",
		    i, sc->sc_memory.page[i].addr);
	}

	sc->sc_memory.pages = i;

	DPRINTF(sc, UPGT_DEBUG_FW, "memory pages=%d\n", sc->sc_memory.pages);
	return (0);
}