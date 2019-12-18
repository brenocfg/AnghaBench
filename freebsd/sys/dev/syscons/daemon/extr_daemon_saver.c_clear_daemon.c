#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * scr_map; TYPE_1__* cur_scp; } ;
typedef  TYPE_2__ sc_softc_t ;
struct TYPE_4__ {int xsize; int /*<<< orphan*/  scr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR (int) ; 
 int BG_BLACK ; 
 int FG_LIGHTGREY ; 
 int /*<<< orphan*/  sc_vtb_erase (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clear_daemon(sc_softc_t *sc, int xpos, int ypos, int dxdir, int xoff, int yoff, 
	    int xlen, int ylen)
{
	int y;

	if (xlen <= 0)
		return;
	for (y = yoff; y < ylen; y++) {
		sc_vtb_erase(&sc->cur_scp->scr,
			     (ypos + y)*sc->cur_scp->xsize + xpos + xoff,
			     xlen - xoff,
			     sc->scr_map[0x20], ATTR(FG_LIGHTGREY | BG_BLACK));
	}
}