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
typedef  int vm_offset_t ;
struct TYPE_3__ {int md_flags; int md_spinlock_count; scalar_t__ md_cop2owner; void* md_ucop2; void* md_cop2; int /*<<< orphan*/  md_saved_intr; int /*<<< orphan*/  md_tls_tcb_offset; int /*<<< orphan*/  md_tls; } ;
struct thread {TYPE_2__* td_frame; TYPE_1__ td_md; struct pcb* td_pcb; } ;
struct proc {int dummy; } ;
struct pcb {int* pcb_context; } ;
typedef  void* register_t ;
typedef  int /*<<< orphan*/  __int64_t ;
struct TYPE_4__ {int v1; int sr; scalar_t__ a3; scalar_t__ v0; } ;

/* Variables and functions */
 int CALLFRAME_SIZ ; 
 scalar_t__ COP2_OWNER_USERLAND ; 
 int MDTD_COP2USED ; 
 int MDTD_FPUSED ; 
 int MIPS_SR_COP_2_BIT ; 
 int /*<<< orphan*/  MIPS_SR_INT_IE ; 
 int MIPS_SR_INT_MASK ; 
 int MIPS_SR_KX ; 
 int MIPS_SR_PX ; 
 int MIPS_SR_SX ; 
 int MIPS_SR_UX ; 
 int /*<<< orphan*/  MipsSaveCurFPState (struct thread*) ; 
 size_t PCB_REG_RA ; 
 size_t PCB_REG_S0 ; 
 size_t PCB_REG_S1 ; 
 size_t PCB_REG_S2 ; 
 size_t PCB_REG_SP ; 
 size_t PCB_REG_SR ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int RFPROC ; 
 int /*<<< orphan*/  bcopy (struct pcb*,struct pcb*,int) ; 
 scalar_t__ fork_return ; 
 scalar_t__ fork_trampoline ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int mips_rd_status () ; 
 void* octeon_cop2_alloc_ctx () ; 
 int /*<<< orphan*/  octeon_cop2_save (void*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
cpu_fork(struct thread *td1, struct proc *p2, struct thread *td2, int flags)
{
	struct pcb *pcb2;

	if ((flags & RFPROC) == 0)
		return;
	/* It is assumed that the vm_thread_alloc called
	 * cpu_thread_alloc() before cpu_fork is called.
	 */

	/* Point the pcb to the top of the stack */
	pcb2 = td2->td_pcb;

	/* Copy td1's pcb, note that in this case
	 * our pcb also includes the td_frame being copied
	 * too. The older mips2 code did an additional copy
	 * of the td_frame, for us that's not needed any
	 * longer (this copy does them both) 
	 */
	bcopy(td1->td_pcb, pcb2, sizeof(*pcb2));

	/* Point mdproc and then copy over td1's contents
	 * md_proc is empty for MIPS
	 */
	td2->td_md.md_flags = td1->td_md.md_flags & MDTD_FPUSED;

	/*
	 * Set up return-value registers as fork() libc stub expects.
	 */
	td2->td_frame->v0 = 0;
	td2->td_frame->v1 = 1;
	td2->td_frame->a3 = 0;

	if (td1 == PCPU_GET(fpcurthread))
		MipsSaveCurFPState(td1);

	pcb2->pcb_context[PCB_REG_RA] = (register_t)(intptr_t)fork_trampoline;
	/* Make sp 64-bit aligned */
	pcb2->pcb_context[PCB_REG_SP] = (register_t)(((vm_offset_t)td2->td_pcb &
	    ~(sizeof(__int64_t) - 1)) - CALLFRAME_SIZ);
	pcb2->pcb_context[PCB_REG_S0] = (register_t)(intptr_t)fork_return;
	pcb2->pcb_context[PCB_REG_S1] = (register_t)(intptr_t)td2;
	pcb2->pcb_context[PCB_REG_S2] = (register_t)(intptr_t)td2->td_frame;
	pcb2->pcb_context[PCB_REG_SR] = mips_rd_status() &
	    (MIPS_SR_KX | MIPS_SR_UX | MIPS_SR_INT_MASK);
	/*
	 * FREEBSD_DEVELOPERS_FIXME:
	 * Setup any other CPU-Specific registers (Not MIPS Standard)
	 * and/or bits in other standard MIPS registers (if CPU-Specific)
	 *  that are needed.
	 */

	td2->td_md.md_tls = td1->td_md.md_tls;
	td2->td_md.md_tls_tcb_offset = td1->td_md.md_tls_tcb_offset;
	td2->td_md.md_saved_intr = MIPS_SR_INT_IE;
	td2->td_md.md_spinlock_count = 1;
#ifdef CPU_CNMIPS
	if (td1->td_md.md_flags & MDTD_COP2USED) {
		if (td1->td_md.md_cop2owner == COP2_OWNER_USERLAND) {
			if (td1->td_md.md_ucop2)
				octeon_cop2_save(td1->td_md.md_ucop2);
			else
				panic("cpu_fork: ucop2 is NULL but COP2 is enabled");
		}
		else {
			if (td1->td_md.md_cop2)
				octeon_cop2_save(td1->td_md.md_cop2);
			else
				panic("cpu_fork: cop2 is NULL but COP2 is enabled");
		}
	}

	if (td1->td_md.md_cop2) {
		td2->td_md.md_cop2 = octeon_cop2_alloc_ctx();
		memcpy(td2->td_md.md_cop2, td1->td_md.md_cop2, 
			sizeof(*td1->td_md.md_cop2));
	}
	if (td1->td_md.md_ucop2) {
		td2->td_md.md_ucop2 = octeon_cop2_alloc_ctx();
		memcpy(td2->td_md.md_ucop2, td1->td_md.md_ucop2, 
			sizeof(*td1->td_md.md_ucop2));
	}
	td2->td_md.md_cop2owner = td1->td_md.md_cop2owner;
	pcb2->pcb_context[PCB_REG_SR] |= MIPS_SR_PX | MIPS_SR_UX | MIPS_SR_KX | MIPS_SR_SX;
	/* Clear COP2 bits for userland & kernel */
	td2->td_frame->sr &= ~MIPS_SR_COP_2_BIT;
	pcb2->pcb_context[PCB_REG_SR] &= ~MIPS_SR_COP_2_BIT;
#endif
}