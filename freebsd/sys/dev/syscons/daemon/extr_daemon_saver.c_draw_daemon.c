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
 int DAEMON_MAX_WIDTH ; 
 int FG_CYAN ; 
 int FG_LIGHTBLUE ; 
 int FG_LIGHTGREY ; 
 int FG_LIGHTRED ; 
 int FG_WHITE ; 
 int FG_YELLOW ; 
 int** daemon_attr ; 
 char** daemon_pic ; 
 int /*<<< orphan*/  sc_vtb_putc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 size_t xflip_symbol (char) ; 

__attribute__((used)) static void
draw_daemon(sc_softc_t *sc, int xpos, int ypos, int dxdir, int xoff, int yoff, 
	    int xlen, int ylen)
{
	int x, y;
	int px;
	int attr;

	for (y = yoff; y < ylen; y++) {
		if (dxdir < 0)
			px = xoff;
		else
			px = DAEMON_MAX_WIDTH - xlen;
		if (px >= strlen(daemon_pic[y]))
			continue;
		for (x = xoff; (x < xlen) && (daemon_pic[y][px] != '\0'); x++, px++) {
			switch (daemon_attr[y][px]) {
			case 'R': attr = FG_LIGHTRED | BG_BLACK; break;
			case 'Y': attr = FG_YELLOW | BG_BLACK; break;
			case 'B': attr = FG_LIGHTBLUE | BG_BLACK; break;
			case 'W': attr = FG_LIGHTGREY | BG_BLACK; break;
			case 'C': attr = FG_CYAN | BG_BLACK; break;
			default: attr = FG_WHITE | BG_BLACK; break;
			}
			if (dxdir < 0) {	/* Moving left */
				sc_vtb_putc(&sc->cur_scp->scr,
					    (ypos + y)*sc->cur_scp->xsize
						 + xpos + x,
					    sc->scr_map[daemon_pic[y][px]],
					    ATTR(attr));
			} else {		/* Moving right */
				sc_vtb_putc(&sc->cur_scp->scr,
					    (ypos + y)*sc->cur_scp->xsize
						+ xpos + DAEMON_MAX_WIDTH 
						- px - 1,
					    sc->scr_map[xflip_symbol(daemon_pic[y][px])], 
					    ATTR(attr));
			}
		}
	}
}