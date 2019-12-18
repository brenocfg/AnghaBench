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
typedef  void* jmp_buf ;

/* Variables and functions */
 char const* KDB_WHY_UNSET ; 
 int /*<<< orphan*/  PC_REGS () ; 
 scalar_t__ cnunavailable () ; 
 int /*<<< orphan*/  db_command_loop () ; 
 int /*<<< orphan*/  db_dot ; 
 scalar_t__ db_inst_count ; 
 int /*<<< orphan*/  db_load_count ; 
 int /*<<< orphan*/  db_print_loc_and_inst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_print_thread () ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_restart_at_pc (int) ; 
 int /*<<< orphan*/  db_script_kdbenter (char const*) ; 
 scalar_t__ db_stop_at_pc (int,int,int*,int*) ; 
 int /*<<< orphan*/  db_store_count ; 
 void* kdb_jmpbuf (void*) ; 
 char* kdb_why ; 
 scalar_t__ setjmp (void*) ; 

__attribute__((used)) static int
db_trap(int type, int code)
{
	jmp_buf jb;
	void *prev_jb;
	bool bkpt, watchpt;
	const char *why;

	/*
	 * Don't handle the trap if the console is unavailable (i.e. it
	 * is in graphics mode).
	 */
	if (cnunavailable())
		return (0);

	if (db_stop_at_pc(type, code, &bkpt, &watchpt)) {
		if (db_inst_count) {
			db_printf("After %d instructions (%d loads, %d stores),\n",
			    db_inst_count, db_load_count, db_store_count);
		}
		prev_jb = kdb_jmpbuf(jb);
		if (setjmp(jb) == 0) {
			db_dot = PC_REGS();
			db_print_thread();
			if (bkpt)
				db_printf("Breakpoint at\t");
			else if (watchpt)
				db_printf("Watchpoint at\t");
			else
				db_printf("Stopped at\t");
			db_print_loc_and_inst(db_dot);
		}
		why = kdb_why;
		db_script_kdbenter(why != KDB_WHY_UNSET ? why : "unknown");
		db_command_loop();
		(void)kdb_jmpbuf(prev_jb);
	}

	db_restart_at_pc(watchpt);

	return (1);
}