#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  inp_rec ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_12__ {scalar_t__ AsciiChar; } ;
struct TYPE_13__ {int /*<<< orphan*/  wVirtualKeyCode; TYPE_1__ uChar; int /*<<< orphan*/  bKeyDown; } ;
struct TYPE_14__ {int /*<<< orphan*/  MouseEvent; TYPE_2__ KeyEvent; } ;
struct TYPE_17__ {scalar_t__ EventType; TYPE_3__ Event; } ;
struct TYPE_16__ {scalar_t__ _keypad_on; } ;
struct TYPE_15__ {int /*<<< orphan*/  inp; } ;
typedef  TYPE_4__ TERMINAL_CONTROL_BLOCK ;
typedef  TYPE_5__ SCREEN ;
typedef  TYPE_6__ INPUT_RECORD ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 scalar_t__ KEY_EVENT ; 
 int KEY_MOUSE ; 
 scalar_t__ MOUSE_EVENT ; 
 int MapKey (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ReadConsoleInput (int /*<<< orphan*/ ,TYPE_6__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  SetSP () ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int /*<<< orphan*/  assert (int*) ; 
 scalar_t__ handle_mouse (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  returnCode (int) ; 

__attribute__((used)) static int
drv_read(TERMINAL_CONTROL_BLOCK * TCB, int *buf)
{
    SCREEN *sp;
    int n = 1;
    INPUT_RECORD inp_rec;
    BOOL b;
    DWORD nRead;
    WORD vk;

    AssertTCB();
    assert(buf);
    SetSP();

    memset(&inp_rec, 0, sizeof(inp_rec));

    T((T_CALLED("win32con::drv_read(%p)"), TCB));
    while ((b = ReadConsoleInput(TCB->inp, &inp_rec, 1, &nRead))) {
	if (b && nRead > 0) {
	    if (inp_rec.EventType == KEY_EVENT) {
		if (!inp_rec.Event.KeyEvent.bKeyDown)
		    continue;
		*buf = (int) inp_rec.Event.KeyEvent.uChar.AsciiChar;
		vk = inp_rec.Event.KeyEvent.wVirtualKeyCode;
		if (*buf == 0) {
		    if (sp->_keypad_on) {
			*buf = MapKey(TCB, vk);
			if (0 > (*buf))
			    continue;
			else
			    break;
		    } else
			continue;
		} else {	/* *buf != 0 */
		    break;
		}
	    } else if (inp_rec.EventType == MOUSE_EVENT) {
		if (handle_mouse(TCB, inp_rec.Event.MouseEvent)) {
		    *buf = KEY_MOUSE;
		    break;
		}
	    }
	    continue;
	}
    }
    returnCode(n);
}