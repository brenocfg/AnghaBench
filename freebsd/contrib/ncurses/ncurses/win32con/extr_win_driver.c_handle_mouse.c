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
typedef  int /*<<< orphan*/  work ;
typedef  int /*<<< orphan*/  mmask_t ;
struct TYPE_10__ {scalar_t__ y; int /*<<< orphan*/  x; int /*<<< orphan*/  bstate; } ;
struct TYPE_7__ {scalar_t__ Y; int /*<<< orphan*/  X; } ;
struct TYPE_9__ {int dwButtonState; TYPE_1__ dwMousePosition; } ;
struct TYPE_8__ {int _drv_mouse_old_buttons; int _drv_mouse_new_buttons; size_t _drv_mouse_tail; TYPE_4__* _drv_mouse_fifo; } ;
typedef  int /*<<< orphan*/  TERMINAL_CONTROL_BLOCK ;
typedef  TYPE_2__ SCREEN ;
typedef  int /*<<< orphan*/  Properties ;
typedef  TYPE_3__ MOUSE_EVENT_RECORD ;
typedef  TYPE_4__ MEVENT ;

/* Variables and functions */
 scalar_t__ AdjustY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AssertTCB () ; 
 int BUTTON_MASK ; 
 int FALSE ; 
 int /*<<< orphan*/ * PropOf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSP () ; 
 int TRUE ; 
 int decode_mouse (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
handle_mouse(TERMINAL_CONTROL_BLOCK * TCB, MOUSE_EVENT_RECORD mer)
{
    SCREEN *sp;
    MEVENT work;
    bool result = FALSE;

    AssertTCB();
    SetSP();

    sp->_drv_mouse_old_buttons = sp->_drv_mouse_new_buttons;
    sp->_drv_mouse_new_buttons = mer.dwButtonState & BUTTON_MASK;

    /*
     * We're only interested if the button is pressed or released.
     * FIXME: implement continuous event-tracking.
     */
    if (sp->_drv_mouse_new_buttons != sp->_drv_mouse_old_buttons) {
	Properties *p = PropOf(TCB);

	memset(&work, 0, sizeof(work));

	if (sp->_drv_mouse_new_buttons) {

	    work.bstate |= (mmask_t) decode_mouse(TCB, sp->_drv_mouse_new_buttons);

	} else {

	    /* cf: BUTTON_PRESSED, BUTTON_RELEASED */
	    work.bstate |= (mmask_t) (decode_mouse(TCB,
						   sp->_drv_mouse_old_buttons)
				      >> 1);

	    result = TRUE;
	}

	work.x = mer.dwMousePosition.X;
	work.y = mer.dwMousePosition.Y - AdjustY(p);

	sp->_drv_mouse_fifo[sp->_drv_mouse_tail] = work;
	sp->_drv_mouse_tail += 1;
    }

    return result;
}