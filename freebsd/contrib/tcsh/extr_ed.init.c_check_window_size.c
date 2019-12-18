#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ChangeSize (int,int) ; 
 int /*<<< orphan*/  ClearDisp () ; 
 int /*<<< orphan*/  ClearLines () ; 
 scalar_t__ GetSize (int*,int*) ; 
 scalar_t__ GettingInput ; 
 int /*<<< orphan*/  MoveToChar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MoveToLine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Refresh () ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disabled_cleanup ; 
 int /*<<< orphan*/  pintr_disabled ; 
 scalar_t__ windowchg ; 

void
check_window_size(int force)
{
    int     lins, cols;

    /* don't want to confuse things here */
    pintr_disabled++;
    cleanup_push(&pintr_disabled, disabled_cleanup);
    /*
     * From: bret@shark.agps.lanl.gov (Bret Thaeler) Avoid sunview bug, where a
     * partially hidden window gets a SIG_WINDOW every time the text is
     * scrolled
     */
    if (GetSize(&lins, &cols) || force) {
	if (GettingInput) {
	    ClearLines();
	    ClearDisp();
	    MoveToLine(0);
	    MoveToChar(0);
	    ChangeSize(lins, cols);
	    Refresh();
	}
	else
	    ChangeSize(lins, cols);
    }
    windowchg = 0;
    cleanup_until(&pintr_disabled);	/* can change it again */
}