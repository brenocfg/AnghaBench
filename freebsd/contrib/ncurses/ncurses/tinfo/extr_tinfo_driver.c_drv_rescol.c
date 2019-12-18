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
typedef  int /*<<< orphan*/  TERMINAL_CONTROL_BLOCK ;
typedef  int /*<<< orphan*/  SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 int FALSE ; 
 int /*<<< orphan*/  NCURSES_PUTP2 (char*,scalar_t__) ; 
 int /*<<< orphan*/  SetSP () ; 
 int TRUE ; 
 scalar_t__ orig_pair ; 

__attribute__((used)) static bool
drv_rescol(TERMINAL_CONTROL_BLOCK * TCB)
{
    bool result = FALSE;
    SCREEN *sp;

    AssertTCB();
    SetSP();

    if (orig_pair != 0) {
	NCURSES_PUTP2("orig_pair", orig_pair);
	result = TRUE;
    }
    return result;
}