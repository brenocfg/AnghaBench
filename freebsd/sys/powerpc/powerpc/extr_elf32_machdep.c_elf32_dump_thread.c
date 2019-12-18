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
typedef  int /*<<< orphan*/  vshr ;
typedef  int /*<<< orphan*/  uint64_t ;
struct thread {struct pcb* td_pcb; } ;
struct TYPE_4__ {TYPE_1__* fpr; } ;
struct pcb {int pcb_flags; TYPE_2__ pcb_fpu; int /*<<< orphan*/  pcb_vec; } ;
struct TYPE_3__ {int /*<<< orphan*/ * vsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NT_PPC_VMX ; 
 int /*<<< orphan*/  NT_PPC_VSX ; 
 int PCB_VEC ; 
 int PCB_VSX ; 
 scalar_t__ elf32_populate_note (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_fpu_nodrop (struct thread*) ; 
 int /*<<< orphan*/  save_vec_nodrop (struct thread*) ; 

void
elf32_dump_thread(struct thread *td, void *dst, size_t *off)
{
	size_t len;
	struct pcb *pcb;
	uint64_t vshr[32];
	uint64_t *vsr_dw1;
	int vsr_idx;

	len = 0;
	pcb = td->td_pcb;

	if (pcb->pcb_flags & PCB_VEC) {
		save_vec_nodrop(td);
		if (dst != NULL) {
			len += elf32_populate_note(NT_PPC_VMX,
			    &pcb->pcb_vec, (char *)dst + len,
			    sizeof(pcb->pcb_vec), NULL);
		} else
			len += elf32_populate_note(NT_PPC_VMX, NULL, NULL,
			    sizeof(pcb->pcb_vec), NULL);
	}

	if (pcb->pcb_flags & PCB_VSX) {
		save_fpu_nodrop(td);
		if (dst != NULL) {
			/*
			 * Doubleword 0 of VSR0-VSR31 overlap with FPR0-FPR31 and
			 * VSR32-VSR63 overlap with VR0-VR31, so we only copy
			 * the non-overlapping data, which is doubleword 1 of VSR0-VSR31.
			 */
			for (vsr_idx = 0; vsr_idx < nitems(vshr); vsr_idx++) {
				vsr_dw1 = (uint64_t *)&pcb->pcb_fpu.fpr[vsr_idx].vsr[2];
				vshr[vsr_idx] = *vsr_dw1;
			}
			len += elf32_populate_note(NT_PPC_VSX,
			    vshr, (char *)dst + len,
			    sizeof(vshr), NULL);
		} else
			len += elf32_populate_note(NT_PPC_VSX, NULL, NULL,
			    sizeof(vshr), NULL);
	}

	*off = len;
}