#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mouse_cut_end; int mouse_cut_start; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int FALSE ; 

int
sc_inside_cutmark(scr_stat *scp, int pos)
{
    int start;
    int end;

    if (scp->mouse_cut_end < 0)
	return FALSE;
    if (scp->mouse_cut_start <= scp->mouse_cut_end) {
	start = scp->mouse_cut_start;
	end = scp->mouse_cut_end;
    } else {
	start = scp->mouse_cut_end;
	end = scp->mouse_cut_start - 1;
    }
    return ((start <= pos) && (pos <= end));
}