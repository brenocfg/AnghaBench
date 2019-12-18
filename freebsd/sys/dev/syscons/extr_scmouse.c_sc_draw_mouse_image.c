#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sc; int /*<<< orphan*/  status; int /*<<< orphan*/  mouse_ypos; int /*<<< orphan*/  mouse_oldypos; int /*<<< orphan*/  mouse_xpos; int /*<<< orphan*/  mouse_oldxpos; int /*<<< orphan*/  mouse_pos; int /*<<< orphan*/  mouse_oldpos; TYPE_1__* rndr; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_6__ {int /*<<< orphan*/  (* draw_mouse ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ISGRAPHSC (TYPE_2__*) ; 
 int /*<<< orphan*/  MOUSE_VISIBLE ; 
 int /*<<< orphan*/  SC_VIDEO_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_VIDEO_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sc_draw_mouse_image(scr_stat *scp)
{
    if (ISGRAPHSC(scp))
	return;

    SC_VIDEO_LOCK(scp->sc);
    (*scp->rndr->draw_mouse)(scp, scp->mouse_xpos, scp->mouse_ypos, TRUE);
    scp->mouse_oldpos = scp->mouse_pos;
    scp->mouse_oldxpos = scp->mouse_xpos;
    scp->mouse_oldypos = scp->mouse_ypos;
    scp->status |= MOUSE_VISIBLE;
    SC_VIDEO_UNLOCK(scp->sc);
}