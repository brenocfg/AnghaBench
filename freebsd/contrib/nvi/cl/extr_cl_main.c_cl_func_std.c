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
struct TYPE_3__ {int /*<<< orphan*/  scr_usage; int /*<<< orphan*/  scr_suspend; int /*<<< orphan*/  scr_split; int /*<<< orphan*/  scr_screen; int /*<<< orphan*/  scr_rename; int /*<<< orphan*/  scr_refresh; int /*<<< orphan*/  scr_optchange; int /*<<< orphan*/ * scr_msg; int /*<<< orphan*/  scr_move; int /*<<< orphan*/  scr_keyval; int /*<<< orphan*/  scr_insertln; int /*<<< orphan*/  scr_fmap; int /*<<< orphan*/  scr_ex_adjust; int /*<<< orphan*/  scr_event; int /*<<< orphan*/  scr_discard; int /*<<< orphan*/ * scr_reply; int /*<<< orphan*/  scr_deleteln; int /*<<< orphan*/  scr_cursor; int /*<<< orphan*/  scr_clrtoeol; int /*<<< orphan*/ * scr_child; int /*<<< orphan*/ * scr_busy; int /*<<< orphan*/  scr_bell; int /*<<< orphan*/  scr_baud; int /*<<< orphan*/  scr_attr; int /*<<< orphan*/  scr_waddstr; int /*<<< orphan*/  scr_addstr; } ;
typedef  TYPE_1__ GS ;

/* Variables and functions */
 int /*<<< orphan*/  cl_addstr ; 
 int /*<<< orphan*/  cl_attr ; 
 int /*<<< orphan*/  cl_baud ; 
 int /*<<< orphan*/  cl_bell ; 
 int /*<<< orphan*/  cl_clrtoeol ; 
 int /*<<< orphan*/  cl_cursor ; 
 int /*<<< orphan*/  cl_deleteln ; 
 int /*<<< orphan*/  cl_discard ; 
 int /*<<< orphan*/  cl_event ; 
 int /*<<< orphan*/  cl_ex_adjust ; 
 int /*<<< orphan*/  cl_fmap ; 
 int /*<<< orphan*/  cl_insertln ; 
 int /*<<< orphan*/  cl_keyval ; 
 int /*<<< orphan*/  cl_move ; 
 int /*<<< orphan*/  cl_optchange ; 
 int /*<<< orphan*/  cl_refresh ; 
 int /*<<< orphan*/  cl_rename ; 
 int /*<<< orphan*/  cl_screen ; 
 int /*<<< orphan*/  cl_split ; 
 int /*<<< orphan*/  cl_suspend ; 
 int /*<<< orphan*/  cl_usage ; 
 int /*<<< orphan*/  cl_waddstr ; 

__attribute__((used)) static void
cl_func_std(GS *gp)
{
	gp->scr_addstr = cl_addstr;
	gp->scr_waddstr = cl_waddstr;
	gp->scr_attr = cl_attr;
	gp->scr_baud = cl_baud;
	gp->scr_bell = cl_bell;
	gp->scr_busy = NULL;
	gp->scr_child = NULL;
	gp->scr_clrtoeol = cl_clrtoeol;
	gp->scr_cursor = cl_cursor;
	gp->scr_deleteln = cl_deleteln;
	gp->scr_reply = NULL;
	gp->scr_discard = cl_discard;
	gp->scr_event = cl_event;
	gp->scr_ex_adjust = cl_ex_adjust;
	gp->scr_fmap = cl_fmap;
	gp->scr_insertln = cl_insertln;
	gp->scr_keyval = cl_keyval;
	gp->scr_move = cl_move;
	gp->scr_msg = NULL;
	gp->scr_optchange = cl_optchange;
	gp->scr_refresh = cl_refresh;
	gp->scr_rename = cl_rename;
	gp->scr_screen = cl_screen;
	gp->scr_split = cl_split;
	gp->scr_suspend = cl_suspend;
	gp->scr_usage = cl_usage;
}