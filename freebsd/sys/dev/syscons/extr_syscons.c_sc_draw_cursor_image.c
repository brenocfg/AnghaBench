#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  sc; int /*<<< orphan*/  cursor_pos; int /*<<< orphan*/  cursor_oldpos; TYPE_2__ curs_attr; TYPE_1__* rndr; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_7__ {int /*<<< orphan*/  (* draw_cursor ) (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CONS_BLINK_CURSOR ; 
 int /*<<< orphan*/  SC_VIDEO_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_VIDEO_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sc_inside_cutmark (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sc_draw_cursor_image(scr_stat *scp)
{
    /* assert(scp == scp->sc->cur_scp); */
    SC_VIDEO_LOCK(scp->sc);
    (*scp->rndr->draw_cursor)(scp, scp->cursor_pos,
			      scp->curs_attr.flags & CONS_BLINK_CURSOR, TRUE,
			      sc_inside_cutmark(scp, scp->cursor_pos));
    scp->cursor_oldpos = scp->cursor_pos;
    SC_VIDEO_UNLOCK(scp->sc);
}