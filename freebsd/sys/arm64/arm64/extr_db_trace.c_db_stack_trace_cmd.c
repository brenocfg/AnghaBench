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
typedef  int /*<<< orphan*/  uint64_t ;
struct unwind_state {int /*<<< orphan*/  fp; int /*<<< orphan*/  sp; int /*<<< orphan*/  pc; } ;
typedef  scalar_t__ db_expr_t ;
typedef  scalar_t__ c_db_sym_t ;

/* Variables and functions */
 scalar_t__ C_DB_SYM_NULL ; 
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int /*<<< orphan*/  DB_STGY_PROC ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_printsym (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ db_search_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  db_symbol_values (scalar_t__,char const**,scalar_t__*) ; 
 int unwind_frame (struct unwind_state*) ; 

__attribute__((used)) static void
db_stack_trace_cmd(struct unwind_state *frame)
{
	c_db_sym_t sym;
	const char *name;
	db_expr_t value;
	db_expr_t offset;

	while (1) {
		uint64_t pc = frame->pc;
		int ret;

		ret = unwind_frame(frame);
		if (ret < 0)
			break;

		sym = db_search_symbol(pc, DB_STGY_ANY, &offset);
		if (sym == C_DB_SYM_NULL) {
			value = 0;
			name = "(null)";
		} else
			db_symbol_values(sym, &name, &value);

		db_printf("%s() at ", name);
		db_printsym(frame->pc, DB_STGY_PROC);
		db_printf("\n");

		db_printf("\t pc = 0x%016lx  lr = 0x%016lx\n", pc,
		    frame->pc);
		db_printf("\t sp = 0x%016lx  fp = 0x%016lx\n", frame->sp,
		    frame->fp);
		/* TODO: Show some more registers */
		db_printf("\n");
	}
}