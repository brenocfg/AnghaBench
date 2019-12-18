#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* sc; int /*<<< orphan*/  base_curs_attr; int /*<<< orphan*/  dflt_curs_attr; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_8__ {TYPE_2__* cur_scp; } ;

/* Variables and functions */
 int CONS_DEFAULT_CURSOR ; 
 int CONS_RESET_CURSOR ; 
 int /*<<< orphan*/  ISGRAPHSC (TYPE_2__*) ; 
 int /*<<< orphan*/  sc_adjust_ca (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  sc_draw_cursor_image (TYPE_2__*) ; 
 int /*<<< orphan*/  sc_remove_cursor_image (TYPE_2__*) ; 
 int /*<<< orphan*/  sc_set_cursor_image (TYPE_2__*) ; 

__attribute__((used)) static void
change_cursor_shape(scr_stat *scp, int flags, int base, int height)
{
    if ((scp == scp->sc->cur_scp) && !ISGRAPHSC(scp))
	sc_remove_cursor_image(scp);

    if (flags & CONS_RESET_CURSOR)
	scp->base_curs_attr = scp->dflt_curs_attr;
    else if (flags & CONS_DEFAULT_CURSOR) {
	sc_adjust_ca(&scp->dflt_curs_attr, flags, base, height);
	scp->base_curs_attr = scp->dflt_curs_attr;
    } else
	sc_adjust_ca(&scp->base_curs_attr, flags, base, height);

    if ((scp == scp->sc->cur_scp) && !ISGRAPHSC(scp)) {
	sc_set_cursor_image(scp);
	sc_draw_cursor_image(scp);
    }
}