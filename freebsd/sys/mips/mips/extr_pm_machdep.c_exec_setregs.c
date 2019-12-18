#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct trapframe {int dummy; } ;
struct TYPE_4__ {scalar_t__ md_tls_tcb_offset; scalar_t__ md_ss_addr; int /*<<< orphan*/  md_flags; } ;
struct thread {TYPE_2__ td_md; TYPE_1__* td_frame; int /*<<< orphan*/  td_proc; } ;
struct image_params {int entry_addr; scalar_t__ ps_strings; } ;
typedef  int register_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_3__ {int sp; int pc; int t9; int sr; int a0; int a3; scalar_t__ a2; scalar_t__ a1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDTD_FPUSED ; 
 int MIPS_SR_EXL ; 
 int MIPS_SR_INT_IE ; 
 int MIPS_SR_INT_MASK ; 
 int MIPS_SR_KSU_USER ; 
 int MIPS_SR_KX ; 
 int MIPS_SR_PX ; 
 int MIPS_SR_UX ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,struct thread*) ; 
 int STACK_ALIGN ; 
 int /*<<< orphan*/  SV_LP64 ; 
 int /*<<< orphan*/  SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLS_TCB_SIZE ; 
 scalar_t__ TLS_TP_OFFSET ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fpcurthread ; 
 int mips_rd_status () ; 

void
exec_setregs(struct thread *td, struct image_params *imgp, u_long stack)
{

	bzero((caddr_t)td->td_frame, sizeof(struct trapframe));

	td->td_frame->sp = ((register_t)stack) & ~(STACK_ALIGN - 1);

	/*
	 * If we're running o32 or n32 programs but have 64-bit registers,
	 * GCC may use stack-relative addressing near the top of user
	 * address space that, due to sign extension, will yield an
	 * invalid address.  For instance, if sp is 0x7fffff00 then GCC
	 * might do something like this to load a word from 0x7ffffff0:
	 *
	 * 	addu	sp, sp, 32768
	 * 	lw	t0, -32528(sp)
	 *
	 * On systems with 64-bit registers, sp is sign-extended to
	 * 0xffffffff80007f00 and the load is instead done from
	 * 0xffffffff7ffffff0.
	 *
	 * To prevent this, we subtract 64K from the stack pointer here
	 * for processes with 32-bit pointers.
	 */
#if defined(__mips_n32) || defined(__mips_n64)
	if (!SV_PROC_FLAG(td->td_proc, SV_LP64))
		td->td_frame->sp -= 65536;
#endif

	td->td_frame->pc = imgp->entry_addr & ~3;
	td->td_frame->t9 = imgp->entry_addr & ~3; /* abicall req */
	td->td_frame->sr = MIPS_SR_KSU_USER | MIPS_SR_EXL | MIPS_SR_INT_IE |
	    (mips_rd_status() & MIPS_SR_INT_MASK);
#if defined(__mips_n32) 
	td->td_frame->sr |= MIPS_SR_PX;
#elif  defined(__mips_n64)
	td->td_frame->sr |= MIPS_SR_PX | MIPS_SR_UX | MIPS_SR_KX;
#endif
	/*
	 * FREEBSD_DEVELOPERS_FIXME:
	 * Setup any other CPU-Specific registers (Not MIPS Standard)
	 * and/or bits in other standard MIPS registers (if CPU-Specific)
	 *  that are needed.
	 */

	/*
	 * Set up arguments for the rtld-capable crt0:
	 *	a0	stack pointer
	 *	a1	rtld cleanup (filled in by dynamic loader)
	 *	a2	rtld object (filled in by dynamic loader)
	 *	a3	ps_strings
	 */
	td->td_frame->a0 = (register_t) stack;
	td->td_frame->a1 = 0;
	td->td_frame->a2 = 0;
	td->td_frame->a3 = (register_t)imgp->ps_strings;

	td->td_md.md_flags &= ~MDTD_FPUSED;
	if (PCPU_GET(fpcurthread) == td)
	    PCPU_SET(fpcurthread, (struct thread *)0);
	td->td_md.md_ss_addr = 0;

	td->td_md.md_tls_tcb_offset = TLS_TP_OFFSET + TLS_TCB_SIZE;
}