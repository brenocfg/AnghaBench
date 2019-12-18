#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_5__ {int /*<<< orphan*/  hdl; } ;
typedef  TYPE_1__ TERMINAL_CONTROL_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 int FALSE ; 
 int FOREGROUND_BLUE ; 
 int FOREGROUND_GREEN ; 
 int FOREGROUND_RED ; 
 int /*<<< orphan*/  SetConsoleTextAttribute (int /*<<< orphan*/ ,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  get_SBI (TYPE_1__*) ; 
 scalar_t__ okConsoleHandle (TYPE_1__*) ; 

__attribute__((used)) static bool
drv_rescol(TERMINAL_CONTROL_BLOCK * TCB)
{
    bool res = FALSE;

    AssertTCB();
    if (okConsoleHandle(TCB)) {
	WORD a = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
	SetConsoleTextAttribute(TCB->hdl, a);
	get_SBI(TCB);
	res = TRUE;
    }
    return res;
}