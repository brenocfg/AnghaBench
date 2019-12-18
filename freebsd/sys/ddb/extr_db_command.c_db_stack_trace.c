#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {scalar_t__ td_tid; TYPE_1__* td_proc; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int db_expr_t ;
struct TYPE_2__ {int p_pid; } ;

/* Variables and functions */
 int db_expression (int*) ; 
 int /*<<< orphan*/  db_flush_lex () ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int db_radix ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_skip_to_eol () ; 
 int /*<<< orphan*/  db_trace_thread (struct thread*,int) ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
 struct thread* kdb_thr_from_pid (int) ; 
 struct thread* kdb_thr_lookup (int /*<<< orphan*/ ) ; 
 struct thread* kdb_thread ; 
 int tCOMMA ; 

__attribute__((used)) static void
db_stack_trace(db_expr_t tid, bool hastid, db_expr_t count, char *modif)
{
	struct thread *td;
	db_expr_t radix;
	pid_t pid;
	int t;

	/*
	 * We parse our own arguments. We don't like the default radix.
	 */
	radix = db_radix;
	db_radix = 10;
	hastid = db_expression(&tid);
	t = db_read_token();
	if (t == tCOMMA) {
		if (!db_expression(&count)) {
			db_printf("Count missing\n");
			db_flush_lex();
			db_radix = radix;
			return;
		}
	} else {
		db_unread_token(t);
		count = -1;
	}
	db_skip_to_eol();
	db_radix = radix;

	if (hastid) {
		td = kdb_thr_lookup((lwpid_t)tid);
		if (td == NULL)
			td = kdb_thr_from_pid((pid_t)tid);
		if (td == NULL) {
			db_printf("Thread %d not found\n", (int)tid);
			return;
		}
	} else
		td = kdb_thread;
	if (td->td_proc != NULL)
		pid = td->td_proc->p_pid;
	else
		pid = -1;
	db_printf("Tracing pid %d tid %ld td %p\n", pid, (long)td->td_tid, td);
	db_trace_thread(td, count);
}