#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int mouse_oldpos; int xsize; int ysize; int /*<<< orphan*/  sc; int /*<<< orphan*/  status; int /*<<< orphan*/  font_size; int /*<<< orphan*/  font_width; int /*<<< orphan*/  mouse_oldypos; int /*<<< orphan*/  mouse_oldxpos; TYPE_1__* rndr; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_7__ {int /*<<< orphan*/  (* draw_mouse ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISGRAPHSC (TYPE_2__*) ; 
 int /*<<< orphan*/  MOUSE_VISIBLE ; 
 int /*<<< orphan*/  SC_VIDEO_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_VIDEO_UNLOCK (int /*<<< orphan*/ ) ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int imax (int,int) ; 
 int imin (int,int) ; 
 int /*<<< orphan*/  mark_for_update (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sc_remove_mouse_image(scr_stat *scp)
{
    int cols, i, rows;

    if (ISGRAPHSC(scp))
	return;

    SC_VIDEO_LOCK(scp->sc);
    (*scp->rndr->draw_mouse)(scp, scp->mouse_oldxpos, scp->mouse_oldypos,
			     FALSE);
    /*
     * To simplify the renderer and ensure undrawing with correct
     * attributes, mark for update a region containing the cursor
     * (usually 2x2 character cells joined by almost a full line o
     * character cells).
     *
     * The renderer should only undraw any pixels outside of the text
     * window (e.g., ones in borders and hardware cursors).
     */
    i = scp->mouse_oldpos;
    mark_for_update(scp, i);
    mark_for_update(scp, i);
    cols = 1 + howmany(10 - 1, scp->font_width); /* up to VGA cursor width 9 */
    cols = imax(cols, 2);	/* in case it is text mode 2x2 char cells */
    cols = imin(cols, scp->xsize - i % scp->xsize);
    rows = 1 + howmany(16 - 1, scp->font_size);	/* up to VGA cursor height 16 */
    rows = imax(rows, 2);	/* don't bother reducing 3 to 2 if text */
    rows = imin(rows, scp->ysize - i / scp->xsize);
    mark_for_update(scp, i + (rows - 1) * scp->xsize + cols - 1);
    scp->status &= ~MOUSE_VISIBLE;
    SC_VIDEO_UNLOCK(scp->sc);
}