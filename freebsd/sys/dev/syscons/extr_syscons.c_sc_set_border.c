#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sc; TYPE_1__* rndr; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_5__ {int /*<<< orphan*/  (* draw_border ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SC_VIDEO_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_VIDEO_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

void
sc_set_border(scr_stat *scp, int color)
{
    SC_VIDEO_LOCK(scp->sc);
    (*scp->rndr->draw_border)(scp, color);
    SC_VIDEO_UNLOCK(scp->sc);
}