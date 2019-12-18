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
 int /*<<< orphan*/  label_off ; 
 int /*<<< orphan*/  label_on ; 

__attribute__((used)) static void
drv_hwlabelOnOff(TERMINAL_CONTROL_BLOCK * TCB, int OnFlag)
{
    SCREEN *sp = TCB->csp;

    AssertTCB();
    if (OnFlag) {
	NCURSES_PUTP2("label_on", label_on);
    } else {
	NCURSES_PUTP2("label_off", label_off);
    }
}