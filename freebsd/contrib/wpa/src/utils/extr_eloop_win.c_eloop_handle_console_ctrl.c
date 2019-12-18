#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  signaled; } ;
struct TYPE_4__ {int /*<<< orphan*/  term_event; TYPE_1__ term_signal; int /*<<< orphan*/  signaled; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CTRL_BREAK_EVENT 129 
#define  CTRL_C_EVENT 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ eloop ; 

__attribute__((used)) static BOOL eloop_handle_console_ctrl(DWORD type)
{
	switch (type) {
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
		eloop.signaled++;
		eloop.term_signal.signaled++;
		SetEvent(eloop.term_event);
		return TRUE;
	default:
		return FALSE;
	}
}