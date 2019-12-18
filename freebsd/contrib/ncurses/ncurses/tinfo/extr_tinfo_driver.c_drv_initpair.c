#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  TYPE_1__ color_t ;
struct TYPE_4__ {TYPE_1__* defaultPalette; } ;
typedef  int /*<<< orphan*/  TERMINAL_CONTROL_BLOCK ;
typedef  int /*<<< orphan*/  SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 scalar_t__ InPalette (int) ; 
 TYPE_2__ InfoOf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NCURSES_PUTP2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSP () ; 
 int /*<<< orphan*/  TPARM_7 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE_ATTRS ; 
 int /*<<< orphan*/ * initialize_pair ; 

__attribute__((used)) static void
drv_initpair(TERMINAL_CONTROL_BLOCK * TCB, int pair, int f, int b)
{
    SCREEN *sp;

    AssertTCB();
    SetSP();

    if ((initialize_pair != NULL) && InPalette(f) && InPalette(b)) {
	const color_t *tp = InfoOf(sp).defaultPalette;

	TR(TRACE_ATTRS,
	   ("initializing pair: pair = %d, fg=(%d,%d,%d), bg=(%d,%d,%d)",
	    pair,
	    tp[f].red, tp[f].green, tp[f].blue,
	    tp[b].red, tp[b].green, tp[b].blue));

	NCURSES_PUTP2("initialize_pair",
		      TPARM_7(initialize_pair,
			      pair,
			      tp[f].red, tp[f].green, tp[f].blue,
			      tp[b].red, tp[b].green, tp[b].blue));
    }
}