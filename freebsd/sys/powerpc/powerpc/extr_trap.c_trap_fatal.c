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
struct trapframe {int srr1; int /*<<< orphan*/  exc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDB_WHY_TRAP ; 
 int /*<<< orphan*/  KDB_WHY_UNSET ; 
 int PSL_PR ; 
 scalar_t__ debugger_on_trap ; 
 int kdb_trap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  kdb_why ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printtrap (int /*<<< orphan*/ ,struct trapframe*,int,int) ; 
 int /*<<< orphan*/  trapname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trap_fatal(struct trapframe *frame)
{
#ifdef KDB
	bool handled;
#endif

	printtrap(frame->exc, frame, 1, (frame->srr1 & PSL_PR));
#ifdef KDB
	if (debugger_on_trap) {
		kdb_why = KDB_WHY_TRAP;
		handled = kdb_trap(frame->exc, 0, frame);
		kdb_why = KDB_WHY_UNSET;
		if (handled)
			return;
	}
#endif
	panic("%s trap", trapname(frame->exc));
}