#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int sv_tm_soff; int sv_t_maxrows; int sv_t_minrows; int sv_t_rows; scalar_t__ sv_tm_coff; scalar_t__ sv_tm_lno; } ;
typedef  TYPE_1__ VI_PRIVATE ;
struct TYPE_14__ {int t_maxrows; int t_minrows; int t_rows; } ;
struct TYPE_13__ {int soff; scalar_t__ coff; scalar_t__ lno; } ;
typedef  TYPE_2__ SMAP ;
typedef  TYPE_3__ SCR ;

/* Variables and functions */
 TYPE_2__* HMAP ; 
 int /*<<< orphan*/  IS_ONELINE (TYPE_3__*) ; 
 scalar_t__ IS_SMALL (TYPE_3__*) ; 
 int /*<<< orphan*/  SMAP_FLUSH (TYPE_2__*) ; 
 TYPE_2__* TMAP ; 
 TYPE_1__* VIP (TYPE_3__*) ; 

__attribute__((used)) static int
txt_map_init(SCR *sp)
{
	SMAP *esmp;
	VI_PRIVATE *vip;

	vip = VIP(sp);
	if (!IS_ONELINE(sp)) {
		/*
		 * Fake like the user is doing input on the last line of the
		 * screen.  This makes all of the scrolling work correctly,
		 * and allows us the use of the vi text editing routines, not
		 * to mention practically infinite length ex commands.
		 *
		 * Save the current location.
		 */
		vip->sv_tm_lno = TMAP->lno;
		vip->sv_tm_soff = TMAP->soff;
		vip->sv_tm_coff = TMAP->coff;
		vip->sv_t_maxrows = sp->t_maxrows;
		vip->sv_t_minrows = sp->t_minrows;
		vip->sv_t_rows = sp->t_rows;

		/*
		 * If it's a small screen, TMAP may be small for the screen.
		 * Fix it, filling in fake lines as we go.
		 */
		if (IS_SMALL(sp))
			for (esmp =
			    HMAP + (sp->t_maxrows - 1); TMAP < esmp; ++TMAP) {
				TMAP[1].lno = TMAP[0].lno + 1;
				TMAP[1].coff = HMAP->coff;
				TMAP[1].soff = 1;
			}

		/* Build the fake entry. */
		TMAP[1].lno = TMAP[0].lno + 1;
		TMAP[1].soff = 1;
		TMAP[1].coff = 0;
		SMAP_FLUSH(&TMAP[1]);
		++TMAP;

		/* Reset the screen information. */
		sp->t_rows = sp->t_minrows = ++sp->t_maxrows;
	}
	return (0);
}