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
struct trapframe {long tf_rsp; long tf_rip; long tf_rbp; int /*<<< orphan*/  tf_rax; int /*<<< orphan*/  tf_trapno; } ;
struct thread {int dummy; } ;
struct amd64_frame {int /*<<< orphan*/  f_frame; int /*<<< orphan*/  f_retaddr; } ;
typedef  int /*<<< orphan*/  db_expr_t ;
typedef  scalar_t__ db_addr_t ;
typedef  int /*<<< orphan*/  c_db_sym_t ;

/* Variables and functions */
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INKERNEL (long) ; 
#define  INTERRUPT 130 
 int NORMAL ; 
#define  SYSCALL 129 
#define  TRAP 128 
 long db_get_value (long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_print_stack_entry (char const*,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_search_symbol (long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_symbol_values (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_syscall (int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static void
db_nextframe(struct amd64_frame **fp, db_addr_t *ip, struct thread *td)
{
	struct trapframe *tf;
	int frame_type;
	long rip, rsp, rbp;
	db_expr_t offset;
	c_db_sym_t sym;
	const char *name;

	rip = db_get_value((long) &(*fp)->f_retaddr, 8, FALSE);
	rbp = db_get_value((long) &(*fp)->f_frame, 8, FALSE);

	/*
	 * Figure out frame type.  We look at the address just before
	 * the saved instruction pointer as the saved EIP is after the
	 * call function, and if the function being called is marked as
	 * dead (such as panic() at the end of dblfault_handler()), then
	 * the instruction at the saved EIP will be part of a different
	 * function (syscall() in this example) rather than the one that
	 * actually made the call.
	 */
	frame_type = NORMAL;
	sym = db_search_symbol(rip - 1, DB_STGY_ANY, &offset);
	db_symbol_values(sym, &name, NULL);
	if (name != NULL) {
		if (strcmp(name, "calltrap") == 0 ||
		    strcmp(name, "fork_trampoline") == 0 ||
		    strcmp(name, "mchk_calltrap") == 0 ||
		    strcmp(name, "nmi_calltrap") == 0 ||
		    strcmp(name, "Xdblfault") == 0)
			frame_type = TRAP;
		else if (strncmp(name, "Xatpic_intr", 11) == 0 ||
		    strncmp(name, "Xapic_isr", 9) == 0 ||
		    strcmp(name, "Xxen_intr_upcall") == 0 ||
		    strcmp(name, "Xtimerint") == 0 ||
		    strcmp(name, "Xipi_intr_bitmap_handler") == 0 ||
		    strcmp(name, "Xcpustop") == 0 ||
		    strcmp(name, "Xcpususpend") == 0 ||
		    strcmp(name, "Xrendezvous") == 0)
			frame_type = INTERRUPT;
		else if (strcmp(name, "Xfast_syscall") == 0 ||
		    strcmp(name, "Xfast_syscall_pti") == 0 ||
		    strcmp(name, "fast_syscall_common") == 0)
			frame_type = SYSCALL;
#ifdef COMPAT_FREEBSD32
		else if (strcmp(name, "Xint0x80_syscall") == 0)
			frame_type = SYSCALL;
#endif
	}

	/*
	 * Normal frames need no special processing.
	 */
	if (frame_type == NORMAL) {
		*ip = (db_addr_t) rip;
		*fp = (struct amd64_frame *) rbp;
		return;
	}

	db_print_stack_entry(name, rip, &(*fp)->f_frame);

	/*
	 * Point to base of trapframe which is just above the
	 * current frame.
	 */
	tf = (struct trapframe *)((long)*fp + 16);

	if (INKERNEL((long) tf)) {
		rsp = tf->tf_rsp;
		rip = tf->tf_rip;
		rbp = tf->tf_rbp;
		switch (frame_type) {
		case TRAP:
			db_printf("--- trap %#r", tf->tf_trapno);
			break;
		case SYSCALL:
			db_printf("--- syscall");
			decode_syscall(tf->tf_rax, td);
			break;
		case INTERRUPT:
			db_printf("--- interrupt");
			break;
		default:
			panic("The moon has moved again.");
		}
		db_printf(", rip = %#lr, rsp = %#lr, rbp = %#lr ---\n", rip,
		    rsp, rbp);
	}

	*ip = (db_addr_t) rip;
	*fp = (struct amd64_frame *) rbp;
}