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
struct TYPE_3__ {int /*<<< orphan*/ * csp; } ;
typedef  TYPE_1__ TERMINAL_CONTROL_BLOCK ;
typedef  int /*<<< orphan*/  SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 int /*<<< orphan*/  NCURSES_PUTP2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPARM_4 (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * initialize_color ; 

__attribute__((used)) static void
drv_initcolor(TERMINAL_CONTROL_BLOCK * TCB,
	      int color, int r, int g, int b)
{
    SCREEN *sp = TCB->csp;

    AssertTCB();
    if (initialize_color != NULL) {
	NCURSES_PUTP2("initialize_color",
		      TPARM_4(initialize_color, color, r, g, b));
    }
}