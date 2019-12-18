#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Left; scalar_t__ Right; scalar_t__ Top; scalar_t__ Bottom; } ;
struct TYPE_5__ {scalar_t__ X; scalar_t__ Y; } ;
struct TYPE_7__ {TYPE_2__ srWindow; TYPE_1__ dwSize; } ;
struct TYPE_8__ {TYPE_3__ SBI; scalar_t__ buffered; } ;
typedef  int /*<<< orphan*/  TERMINAL_CONTROL_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 int ERR ; 
 int OK ; 
 TYPE_4__* PropOf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 scalar_t__ okConsoleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  returnCode (int) ; 

__attribute__((used)) static int
drv_size(TERMINAL_CONTROL_BLOCK * TCB, int *Lines, int *Cols)
{
    int result = ERR;

    AssertTCB();

    T((T_CALLED("win32con::drv_size(%p)"), TCB));

    if (okConsoleHandle(TCB) &&
	PropOf(TCB) != 0 &&
	Lines != NULL &&
	Cols != NULL) {
	if (PropOf(TCB)->buffered) {
	    *Lines = (int) (PropOf(TCB)->SBI.dwSize.Y);
	    *Cols = (int) (PropOf(TCB)->SBI.dwSize.X);
	} else {
	    *Lines = (int) (PropOf(TCB)->SBI.srWindow.Bottom + 1 -
			    PropOf(TCB)->SBI.srWindow.Top);
	    *Cols = (int) (PropOf(TCB)->SBI.srWindow.Right + 1 -
			   PropOf(TCB)->SBI.srWindow.Left);
	}
	result = OK;
    }
    returnCode(result);
}