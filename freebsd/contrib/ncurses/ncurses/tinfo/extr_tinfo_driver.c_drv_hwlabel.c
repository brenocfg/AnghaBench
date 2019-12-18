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
 int /*<<< orphan*/  TPARM_2 (int /*<<< orphan*/ ,int,char*) ; 
 int num_labels ; 
 int /*<<< orphan*/  plab_norm ; 

__attribute__((used)) static void
drv_hwlabel(TERMINAL_CONTROL_BLOCK * TCB, int labnum, char *text)
{
    SCREEN *sp = TCB->csp;

    AssertTCB();
    if (labnum > 0 && labnum <= num_labels) {
	NCURSES_PUTP2("plab_norm",
		      TPARM_2(plab_norm, labnum, text));
    }
}