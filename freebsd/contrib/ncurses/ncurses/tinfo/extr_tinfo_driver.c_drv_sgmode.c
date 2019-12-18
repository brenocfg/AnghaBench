#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  _notty; } ;
struct TYPE_6__ {int /*<<< orphan*/  Filedes; } ;
struct TYPE_5__ {TYPE_3__* csp; } ;
typedef  int /*<<< orphan*/  TTY ;
typedef  TYPE_1__ TERMINAL_CONTROL_BLOCK ;
typedef  TYPE_2__ TERMINAL ;
typedef  TYPE_3__ SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 scalar_t__ EINTR ; 
 scalar_t__ ENOTTY ; 
 int ERR ; 
 scalar_t__ GET_TTY (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int OK ; 
 scalar_t__ SET_TTY (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ errno ; 

__attribute__((used)) static int
drv_sgmode(TERMINAL_CONTROL_BLOCK * TCB, int setFlag, TTY * buf)
{
    SCREEN *sp = TCB->csp;
    TERMINAL *_term = (TERMINAL *) TCB;
    int result = OK;

    AssertTCB();
    if (setFlag) {
	for (;;) {
	    if (SET_TTY(_term->Filedes, buf) != 0) {
		if (errno == EINTR)
		    continue;
		if (errno == ENOTTY) {
		    if (sp)
			sp->_notty = TRUE;
		}
		result = ERR;
	    }
	    break;
	}
    } else {
	for (;;) {
	    if (GET_TTY(_term->Filedes, buf) != 0) {
		if (errno == EINTR)
		    continue;
		result = ERR;
	    }
	    break;
	}
    }
    return result;
}