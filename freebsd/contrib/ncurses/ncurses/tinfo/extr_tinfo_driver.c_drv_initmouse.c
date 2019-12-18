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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  term_names; } ;
struct TYPE_8__ {TYPE_1__ type; } ;
struct TYPE_7__ {int /*<<< orphan*/  _keytry; } ;
typedef  int /*<<< orphan*/  TERMINAL_CONTROL_BLOCK ;
typedef  TYPE_2__ SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 int /*<<< orphan*/  KEY_MOUSE ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  SetSP () ; 
 TYPE_4__* TerminalOf (TYPE_2__*) ; 
 scalar_t__ _nc_add_to_try (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_xterm_mouse (TYPE_2__*) ; 
 scalar_t__ key_mouse ; 
 int /*<<< orphan*/  strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xterm_kmous ; 

__attribute__((used)) static void
drv_initmouse(TERMINAL_CONTROL_BLOCK * TCB)
{
    SCREEN *sp;

    AssertTCB();
    SetSP();

    /* we know how to recognize mouse events under "xterm" */
    if (sp != 0) {
	if (key_mouse != 0) {
	    if (!strcmp(key_mouse, xterm_kmous)
		|| strstr(TerminalOf(sp)->type.term_names, "xterm") != 0) {
		init_xterm_mouse(sp);
	    }
	} else if (strstr(TerminalOf(sp)->type.term_names, "xterm") != 0) {
	    if (_nc_add_to_try(&(sp->_keytry), xterm_kmous, KEY_MOUSE) == OK)
		init_xterm_mouse(sp);
	}
    }
}