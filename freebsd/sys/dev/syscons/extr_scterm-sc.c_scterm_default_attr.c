#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fg; int bg; } ;
struct TYPE_7__ {int fg; int bg; } ;
struct TYPE_9__ {int /*<<< orphan*/  cur_attr; TYPE_2__ std_color; TYPE_2__ cur_color; TYPE_1__ dflt_rev_color; TYPE_1__ rev_color; TYPE_2__ dflt_std_color; } ;
typedef  TYPE_3__ term_stat ;
struct TYPE_10__ {TYPE_3__* ts; } ;
typedef  TYPE_4__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  mask2attr (TYPE_3__*) ; 

__attribute__((used)) static void
scterm_default_attr(scr_stat *scp, int color, int rev_color)
{
	term_stat *tcp = scp->ts;

	tcp->dflt_std_color.fg = color & 0x0f;
	tcp->dflt_std_color.bg = (color >> 4) & 0x0f;
	tcp->dflt_rev_color.fg = rev_color & 0x0f;
	tcp->dflt_rev_color.bg = (rev_color >> 4) & 0x0f;
	tcp->std_color = tcp->dflt_std_color;
	tcp->rev_color = tcp->dflt_rev_color;
	tcp->cur_color = tcp->std_color;
	tcp->cur_attr = mask2attr(tcp);
}