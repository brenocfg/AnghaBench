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
 int SIGEMT ; 
 int SIGFPE ; 
 int SIGILL ; 
 int SIGSEGV ; 
 int SIGTRAP ; 
 int SIGURG ; 
 int T_USER ; 

int
gdb_cpu_signal(int type, int code)
{

	switch (type & ~T_USER) {
	case 0: return (SIGFPE);	/* Divide by zero. */
	case 1: return (SIGTRAP);	/* Debug exception. */
	case 3: return (SIGTRAP);	/* Breakpoint. */
	case 4: return (SIGURG);	/* into instr. (overflow). */
	case 5: return (SIGURG);	/* bound instruction. */
	case 6: return (SIGILL);	/* Invalid opcode. */
	case 7: return (SIGFPE);	/* Coprocessor not present. */
	case 8: return (SIGEMT);	/* Double fault. */
	case 9: return (SIGSEGV);	/* Coprocessor segment overrun. */
	case 10: return (SIGTRAP);	/* Invalid TSS (also single-step). */
	case 11: return (SIGSEGV);	/* Segment not present. */
	case 12: return (SIGSEGV);	/* Stack exception. */
	case 13: return (SIGSEGV);	/* General protection. */
	case 14: return (SIGSEGV);	/* Page fault. */
	case 16: return (SIGEMT);	/* Coprocessor error. */
	}
	return (SIGEMT);
}