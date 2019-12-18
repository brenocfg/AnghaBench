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

/* Variables and functions */
 int KDB_REQ_DEBUGGER ; 
 int /*<<< orphan*/  KDB_WHY_BREAK ; 
 int /*<<< orphan*/  kdb_break_to_debugger ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 

int
kdb_break(void)
{

	if (!kdb_break_to_debugger)
		return (0);
	kdb_enter(KDB_WHY_BREAK, "Break to debugger");
	return (KDB_REQ_DEBUGGER);
}