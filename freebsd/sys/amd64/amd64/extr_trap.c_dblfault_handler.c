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
struct trapframe {int /*<<< orphan*/  tf_gs; int /*<<< orphan*/  tf_fs; int /*<<< orphan*/  tf_es; int /*<<< orphan*/  tf_ds; int /*<<< orphan*/  tf_ss; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_rflags; int /*<<< orphan*/  tf_r15; int /*<<< orphan*/  tf_r14; int /*<<< orphan*/  tf_r13; int /*<<< orphan*/  tf_r12; int /*<<< orphan*/  tf_r11; int /*<<< orphan*/  tf_r10; int /*<<< orphan*/  tf_r9; int /*<<< orphan*/  tf_r8; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rdi; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rbx; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rax; int /*<<< orphan*/  tf_rbp; int /*<<< orphan*/  tf_rsp; int /*<<< orphan*/  tf_rip; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_FSBASE ; 
 int /*<<< orphan*/  MSR_GSBASE ; 
 int /*<<< orphan*/  MSR_KGSBASE ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_id ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  dtrace_doubletrap_func () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

void
dblfault_handler(struct trapframe *frame)
{
#ifdef KDTRACE_HOOKS
	if (dtrace_doubletrap_func != NULL)
		(*dtrace_doubletrap_func)();
#endif
	printf("\nFatal double fault\n"
	    "rip %#lx rsp %#lx rbp %#lx\n"
	    "rax %#lx rdx %#lx rbx %#lx\n"
	    "rcx %#lx rsi %#lx rdi %#lx\n"
	    "r8 %#lx r9 %#lx r10 %#lx\n"
	    "r11 %#lx r12 %#lx r13 %#lx\n"
	    "r14 %#lx r15 %#lx rflags %#lx\n"
	    "cs %#lx ss %#lx ds %#hx es %#hx fs %#hx gs %#hx\n"
	    "fsbase %#lx gsbase %#lx kgsbase %#lx\n",
	    frame->tf_rip, frame->tf_rsp, frame->tf_rbp,
	    frame->tf_rax, frame->tf_rdx, frame->tf_rbx,
	    frame->tf_rcx, frame->tf_rdi, frame->tf_rsi,
	    frame->tf_r8, frame->tf_r9, frame->tf_r10,
	    frame->tf_r11, frame->tf_r12, frame->tf_r13,
	    frame->tf_r14, frame->tf_r15, frame->tf_rflags,
	    frame->tf_cs, frame->tf_ss, frame->tf_ds, frame->tf_es,
	    frame->tf_fs, frame->tf_gs,
	    rdmsr(MSR_FSBASE), rdmsr(MSR_GSBASE), rdmsr(MSR_KGSBASE));
#ifdef SMP
	/* two separate prints in case of a trap on an unmapped page */
	printf("cpuid = %d; ", PCPU_GET(cpuid));
	printf("apic id = %02x\n", PCPU_GET(apic_id));
#endif
	panic("double fault");
}