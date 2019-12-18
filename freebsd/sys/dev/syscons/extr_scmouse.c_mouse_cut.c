#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mouse_cut_start; int mouse_cut_end; int mouse_pos; int xsize; int /*<<< orphan*/  vtb; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SPACE_CHAR (int) ; 
 int /*<<< orphan*/  mouse_do_cut (TYPE_1__*,int,int) ; 
 int sc_vtb_getc (int /*<<< orphan*/ *,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
mouse_cut(scr_stat *scp)
{
    int start;
    int end;
    int from;
    int to;
    int c;
    int p;
    int s;
    int i;

    start = scp->mouse_cut_start;
    end = scp->mouse_cut_end;
    if (scp->mouse_pos >= start) {
	from = start;
	to = end = scp->mouse_pos;
    } else {
	from = end = scp->mouse_pos;
	to = start - 1;
    }
    p = to;
    for (i = p % scp->xsize; i < scp->xsize; ++i) {
	c = sc_vtb_getc(&scp->vtb, p);
	if (!IS_SPACE_CHAR(c))
	    break;
	++p;
    }
    /* if there is nothing but blank chars, trim them, but mark towards eol */
    if (i == scp->xsize) {
	if (end >= start)
	    to = end = p - 1;
	else
	    to = start = p;
    }
    mouse_do_cut(scp, from, to);
    s = spltty();
    scp->mouse_cut_start = start;
    scp->mouse_cut_end = end;
    splx(s);
}