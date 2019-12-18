#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int dsisr; } ;
struct TYPE_4__ {int esr; } ;
struct TYPE_6__ {TYPE_2__ aim; TYPE_1__ booke; } ;
struct trapframe {int srr1; int exc; scalar_t__* fixreg; TYPE_3__ cpu; int /*<<< orphan*/  ctr; scalar_t__ xer; scalar_t__ cr; scalar_t__ srr0; int /*<<< orphan*/  dar; } ;
struct thread {int dummy; } ;
typedef  int db_addr_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 int CALLOFFSET ; 
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int /*<<< orphan*/  DB_STGY_PROC ; 
 int DSISR_STORE ; 
 int ESR_ST ; 
#define  EXC_ALI 148 
#define  EXC_BPT 147 
#define  EXC_DECR 146 
#define  EXC_DSE 145 
#define  EXC_DSI 144 
#define  EXC_EXI 143 
#define  EXC_FPA 142 
#define  EXC_FPU 141 
#define  EXC_ISE 140 
#define  EXC_ISI 139 
#define  EXC_MCHK 138 
#define  EXC_PERF 137 
#define  EXC_PGM 136 
#define  EXC_RST 135 
#define  EXC_RUNMODETRC 134 
#define  EXC_SC 133 
#define  EXC_SMI 132 
#define  EXC_SOFT_PATCH 131 
#define  EXC_TRC 130 
#define  EXC_VEC 129 
#define  EXC_VSX 128 
 void* FALSE ; 
 int PAGE_SIZE ; 
 int PSL_PR ; 
 void* TRUE ; 
 int /*<<< orphan*/  asttrapexit ; 
 int /*<<< orphan*/  db_pager_quit ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_printsym (int,int /*<<< orphan*/ ) ; 
 char* modif ; 
 void* trace_thread ; 
 int /*<<< orphan*/  trapexit ; 

__attribute__((used)) static int
db_backtrace(struct thread *td, db_addr_t fp, int count)
{
	db_addr_t stackframe, lr, *args;
	boolean_t kernel_only = TRUE;
	boolean_t full = FALSE;

#if 0
	{
		register char *cp = modif;
		register char c;

		while ((c = *cp++) != 0) {
			if (c == 't')
				trace_thread = TRUE;
			if (c == 'u')
				kernel_only = FALSE;
			if (c == 'f')
				full = TRUE;
		}
	}
#endif

	stackframe = fp;

	while (!db_pager_quit) {
		if (stackframe < PAGE_SIZE)
			break;

		/*
		 * Locate the next frame by grabbing the backchain ptr
		 * from frame[0]
		 */
		stackframe = *(db_addr_t *)stackframe;

	next_frame:
	    #ifdef __powerpc64__
		/* The saved arg values start at frame[6] */
		args = (db_addr_t *)(stackframe + 48);
	    #else
		/* The saved arg values start at frame[2] */
		args = (db_addr_t *)(stackframe + 8);
	    #endif

		if (stackframe < PAGE_SIZE)
			break;

	        if (count-- == 0)
			break;

		/*
		 * Extract link register from frame and subtract
		 * 4 to convert into calling address (as opposed to
		 * return address)
		 */
	    #ifdef __powerpc64__
		lr = *(db_addr_t *)(stackframe + 16) - 4;
	    #else
		lr = *(db_addr_t *)(stackframe + 4) - 4;
	    #endif
		if ((lr & 3) || (lr < 0x100)) {
			db_printf("saved LR(0x%zx) is invalid.", lr);
			break;
		}

		#ifdef __powerpc64__
		db_printf("0x%016lx: ", stackframe);
		#else
		db_printf("0x%08x: ", stackframe);
		#endif

		/*
		 * The trap code labels the return addresses from the
		 * call to C code as 'trapexit' and 'asttrapexit. Use this
		 * to determine if the callframe has to traverse a saved
		 * trap context
		 */
		if ((lr + CALLOFFSET == (db_addr_t) &trapexit) ||
		    (lr + CALLOFFSET == (db_addr_t) &asttrapexit)) {
			const char *trapstr;
			struct trapframe *tf = (struct trapframe *)(args);
			db_printf("%s ", tf->srr1 & PSL_PR ? "user" : "kernel");
			switch (tf->exc) {
			case EXC_DSI:
				/* XXX take advantage of the union. */
#ifdef BOOKE
				db_printf("DSI %s trap @ %#zx by ",
				    (tf->cpu.booke.esr & ESR_ST) ? "write"
				    : "read", tf->dar);
#else
				db_printf("DSI %s trap @ %#zx by ",
				    (tf->cpu.aim.dsisr & DSISR_STORE) ? "write"
				    : "read", tf->dar);
#endif
				goto print_trap;
			case EXC_ALI:
				db_printf("ALI trap @ %#zx (xSR %#x) ",
				    tf->dar, (uint32_t)tf->cpu.aim.dsisr);
				goto print_trap;
#ifdef __powerpc64__
			case EXC_DSE:
				db_printf("DSE trap @ %#zx by ", tf->dar);
				goto print_trap;
			case EXC_ISE:
				db_printf("ISE trap @ %#zx by ", tf->srr0);
				goto print_trap;
#endif
			case EXC_ISI: trapstr = "ISI"; break;
			case EXC_PGM: trapstr = "PGM"; break;
			case EXC_SC: trapstr = "SC"; break;
			case EXC_EXI: trapstr = "EXI"; break;
			case EXC_MCHK: trapstr = "MCHK"; break;
			case EXC_VEC: trapstr = "VEC"; break;
#if !defined(BOOKE)
			case EXC_FPA: trapstr = "FPA"; break;
			case EXC_BPT: trapstr = "BPT"; break;
			case EXC_TRC: trapstr = "TRC"; break;
			case EXC_RUNMODETRC: trapstr = "RUNMODETRC"; break;
			case EXC_SMI: trapstr = "SMI"; break;
			case EXC_RST: trapstr = "RST"; break;
#endif
			case EXC_FPU: trapstr = "FPU"; break;
			case EXC_DECR: trapstr = "DECR"; break;
			case EXC_PERF: trapstr = "PERF"; break;
			case EXC_VSX: trapstr = "VSX"; break;
			case EXC_SOFT_PATCH: trapstr = "SOFT_PATCH"; break;
			default: trapstr = NULL; break;
			}
			if (trapstr != NULL) {
				db_printf("%s trap by ", trapstr);
			} else {
				db_printf("trap %#zx by ", tf->exc);
			}

		   print_trap:
			lr = (db_addr_t) tf->srr0;
			db_printsym(lr, DB_STGY_ANY);
			db_printf(": srr1=%#zx\n", tf->srr1);
			db_printf("%-10s  r1=%#zx cr=%#x xer=%#x ctr=%#zx",
			    "", tf->fixreg[1], (uint32_t)tf->cr,
			    (uint32_t)tf->xer, tf->ctr);
#ifdef __powerpc64__
			db_printf(" r2=%#zx", tf->fixreg[2]);
#endif
			if (tf->exc == EXC_DSI)
				db_printf(" sr=%#x",
				    (uint32_t)tf->cpu.aim.dsisr);
			db_printf(" frame=%p\n", tf);
			stackframe = (db_addr_t) tf->fixreg[1];
			if (kernel_only && (tf->srr1 & PSL_PR))
				break;
			goto next_frame;
		}

		db_printf("at ");
		db_printsym(lr, DB_STGY_PROC);
		if (full)
			/* Print all the args stored in that stackframe. */
			db_printf("(%zx, %zx, %zx, %zx, %zx, %zx, %zx, %zx)",
				args[0], args[1], args[2], args[3],
				args[4], args[5], args[6], args[7]);
		db_printf("\n");
	}

	return (0);
}