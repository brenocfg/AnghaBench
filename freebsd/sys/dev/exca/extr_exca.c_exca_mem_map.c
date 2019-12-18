#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct exca_softc {int memalloc; int flags; TYPE_1__* mem; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int addr; int size; int realsize; int kind; scalar_t__ cardaddr; int /*<<< orphan*/  memh; int /*<<< orphan*/  memt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,int,int,scalar_t__) ; 
 int EINVAL ; 
 int ENOSPC ; 
 int EXCA_HAS_MEMREG_WIN ; 
 scalar_t__ EXCA_MEMREG_WIN_SHIFT ; 
 int EXCA_MEM_PAGESIZE ; 
 int EXCA_MEM_WINS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exca_do_mem_map (struct exca_softc*,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 int rman_get_end (struct resource*) ; 
 int rman_get_start (struct resource*) ; 

int
exca_mem_map(struct exca_softc *sc, int kind, struct resource *res)
{
	int win;

	for (win = 0; win < EXCA_MEM_WINS; win++) {
		if ((sc->memalloc & (1 << win)) == 0) {
			sc->memalloc |= (1 << win);
			break;
		}
	}
	if (win >= EXCA_MEM_WINS)
		return (ENOSPC);
	if (sc->flags & EXCA_HAS_MEMREG_WIN) {
#ifdef __LP64__
		if (rman_get_start(res) >> (EXCA_MEMREG_WIN_SHIFT + 8) != 0) {
			device_printf(sc->dev,
			    "Does not support mapping above 4GB.");
			return (EINVAL);
		}
#endif
	} else {
		if (rman_get_start(res) >> EXCA_MEMREG_WIN_SHIFT != 0) {
			device_printf(sc->dev,
			    "Does not support mapping above 16M.");
			return (EINVAL);
		}
	}

	sc->mem[win].cardaddr = 0;
	sc->mem[win].memt = rman_get_bustag(res);
	sc->mem[win].memh = rman_get_bushandle(res);
	sc->mem[win].addr = rman_get_start(res);
	sc->mem[win].size = rman_get_end(res) - sc->mem[win].addr + 1;
	sc->mem[win].realsize = sc->mem[win].size + EXCA_MEM_PAGESIZE - 1;
	sc->mem[win].realsize = sc->mem[win].realsize -
	    (sc->mem[win].realsize % EXCA_MEM_PAGESIZE);
	sc->mem[win].kind = kind;
	DPRINTF("exca_mem_map window %d bus %x+%x card addr %x\n",
	    win, sc->mem[win].addr, sc->mem[win].size, sc->mem[win].cardaddr);
	exca_do_mem_map(sc, win);

	return (0);
}