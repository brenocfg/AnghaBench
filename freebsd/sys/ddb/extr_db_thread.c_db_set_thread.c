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
struct thread {scalar_t__ td_tid; } ;
typedef  scalar_t__ db_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_REGS () ; 
 int /*<<< orphan*/  db_dot ; 
 struct thread* db_lookup_thread (scalar_t__,int) ; 
 int /*<<< orphan*/  db_print_loc_and_inst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_print_thread () ; 
 int /*<<< orphan*/  db_printf (char*,int) ; 
 int kdb_thr_select (struct thread*) ; 

void
db_set_thread(db_expr_t tid, bool hastid, db_expr_t cnt, char *mod)
{
	struct thread *thr;
	int err;

	if (hastid) {
		thr = db_lookup_thread(tid, false);
		if (thr != NULL) {
			err = kdb_thr_select(thr);
			if (err != 0) {
				db_printf("unable to switch to thread %ld\n",
				    (long)thr->td_tid);
				return;
			}
			db_dot = PC_REGS();
		} else {
			db_printf("%d: invalid thread\n", (int)tid);
			return;
		}
	}

	db_print_thread();
	db_print_loc_and_inst(PC_REGS());
}