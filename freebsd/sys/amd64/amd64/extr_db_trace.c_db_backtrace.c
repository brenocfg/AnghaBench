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
struct trapframe {int tf_rsp; scalar_t__ tf_rbp; } ;
struct thread {int dummy; } ;
struct amd64_frame {int /*<<< orphan*/  f_retaddr; } ;
typedef  scalar_t__ register_t ;
typedef  scalar_t__ db_expr_t ;
typedef  long db_addr_t ;
typedef  scalar_t__ c_db_sym_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ C_DB_SYM_NULL ; 
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int /*<<< orphan*/  DB_STGY_PROC ; 
 scalar_t__ FALSE ; 
 scalar_t__ INKERNEL (long) ; 
 scalar_t__ TRUE ; 
 void* db_get_value (long,int,scalar_t__) ; 
 int /*<<< orphan*/  db_nextframe (struct amd64_frame**,long*,struct thread*) ; 
 int /*<<< orphan*/  db_pager_quit ; 
 int /*<<< orphan*/  db_print_stack_entry (char const*,long,struct amd64_frame*) ; 
 scalar_t__ db_search_symbol (long,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  db_symbol_values (scalar_t__,char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
db_backtrace(struct thread *td, struct trapframe *tf, struct amd64_frame *frame,
    db_addr_t pc, register_t sp, int count)
{
	struct amd64_frame *actframe;
	const char *name;
	db_expr_t offset;
	c_db_sym_t sym;
	boolean_t first;

	if (count == -1)
		count = 1024;

	first = TRUE;
	while (count-- && !db_pager_quit) {
		sym = db_search_symbol(pc, DB_STGY_ANY, &offset);
		db_symbol_values(sym, &name, NULL);

		/*
		 * Attempt to determine a (possibly fake) frame that gives
		 * the caller's pc.  It may differ from `frame' if the
		 * current function never sets up a standard frame or hasn't
		 * set one up yet or has just discarded one.  The last two
		 * cases can be guessed fairly reliably for code generated
		 * by gcc.  The first case is too much trouble to handle in
		 * general because the amount of junk on the stack depends
		 * on the pc (the special handling of "calltrap", etc. in
		 * db_nextframe() works because the `next' pc is special).
		 */
		actframe = frame;
		if (first) {
			first = FALSE;
			if (sym == C_DB_SYM_NULL && sp != 0) {
				/*
				 * If a symbol couldn't be found, we've probably
				 * jumped to a bogus location, so try and use
				 * the return address to find our caller.
				 */
				db_print_stack_entry(name, pc, NULL);
				pc = db_get_value(sp, 8, FALSE);
				if (db_search_symbol(pc, DB_STGY_PROC,
				    &offset) == C_DB_SYM_NULL)
					break;
				continue;
			} else if (tf != NULL) {
				int instr;

				instr = db_get_value(pc, 4, FALSE);
				if ((instr & 0xffffffff) == 0xe5894855) {
					/* pushq %rbp; movq %rsp, %rbp */
					actframe = (void *)(tf->tf_rsp - 8);
				} else if ((instr & 0xffffff) == 0xe58948) {
					/* movq %rsp, %rbp */
					actframe = (void *)tf->tf_rsp;
					if (tf->tf_rbp == 0) {
						/* Fake frame better. */
						frame = actframe;
					}
				} else if ((instr & 0xff) == 0xc3) {
					/* ret */
					actframe = (void *)(tf->tf_rsp - 8);
				} else if (offset == 0) {
					/* Probably an assembler symbol. */
					actframe = (void *)(tf->tf_rsp - 8);
				}
			} else if (name != NULL &&
			    strcmp(name, "fork_trampoline") == 0) {
				/*
				 * Don't try to walk back on a stack for a
				 * process that hasn't actually been run yet.
				 */
				db_print_stack_entry(name, pc, actframe);
				break;
			}
		}

		db_print_stack_entry(name, pc, actframe);

		if (actframe != frame) {
			/* `frame' belongs to caller. */
			pc = (db_addr_t)
			    db_get_value((long)&actframe->f_retaddr, 8, FALSE);
			continue;
		}

		db_nextframe(&frame, &pc, td);

		if (INKERNEL((long)pc) && !INKERNEL((long)frame)) {
			sym = db_search_symbol(pc, DB_STGY_ANY, &offset);
			db_symbol_values(sym, &name, NULL);
			db_print_stack_entry(name, pc, frame);
			break;
		}
		if (!INKERNEL((long) frame)) {
			break;
		}
	}

	return (0);
}