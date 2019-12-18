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
struct thread {scalar_t__ td_kstack; scalar_t__ td_tid; } ;
typedef  void* jmp_buf ;
typedef  int /*<<< orphan*/  db_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_pager_quit ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 scalar_t__ db_trace_thread (struct thread*,int) ; 
 void* kdb_jmpbuf (void*) ; 
 struct thread* kdb_thr_first () ; 
 struct thread* kdb_thr_next (struct thread*) ; 
 scalar_t__ setjmp (void*) ; 

void
db_show_threads(db_expr_t addr, bool hasaddr, db_expr_t cnt, char *mod)
{
	jmp_buf jb;
	void *prev_jb;
	struct thread *thr;

	thr = kdb_thr_first();
	while (!db_pager_quit && thr != NULL) {
		db_printf("  %6ld (%p) (stack %p)  ", (long)thr->td_tid, thr,
		    (void *)thr->td_kstack);
		prev_jb = kdb_jmpbuf(jb);
		if (setjmp(jb) == 0) {
			if (db_trace_thread(thr, 1) != 0)
				db_printf("***\n");
		}
		kdb_jmpbuf(prev_jb);
		thr = kdb_thr_next(thr);
	}
}