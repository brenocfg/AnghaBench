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
typedef  size_t u_char ;
struct TYPE_5__ {int /*<<< orphan*/ * scr_map; TYPE_1__* cur_scp; } ;
typedef  TYPE_2__ sc_softc_t ;
struct TYPE_4__ {int xsize; int /*<<< orphan*/  scr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR (int) ; 
 int BG_BLACK ; 
 int FG_LIGHTGREEN ; 
 int /*<<< orphan*/  sc_vtb_putc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
draw_string(sc_softc_t *sc, int xpos, int ypos, int xoff, u_char *s, int len)
{
	int x;

	for (x = xoff; x < len; x++)
		sc_vtb_putc(&sc->cur_scp->scr,
			    ypos*sc->cur_scp->xsize + xpos + x,
			    sc->scr_map[s[x]], ATTR(FG_LIGHTGREEN | BG_BLACK));
}