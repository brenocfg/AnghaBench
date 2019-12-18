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
struct vmcb_state {int /*<<< orphan*/  efer; int /*<<< orphan*/  cr4; int /*<<< orphan*/  cr0; int /*<<< orphan*/  cr3; } ;
struct vmcb {struct vmcb_state state; } ;
struct vm_guest_paging {int /*<<< orphan*/  paging_mode; int /*<<< orphan*/  cpu_mode; int /*<<< orphan*/  cpl; int /*<<< orphan*/  cr3; } ;

/* Variables and functions */
 int /*<<< orphan*/  svm_cpl (struct vmcb_state*) ; 
 int /*<<< orphan*/  svm_paging_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svm_vcpu_mode (struct vmcb*) ; 

__attribute__((used)) static void
svm_paging_info(struct vmcb *vmcb, struct vm_guest_paging *paging)
{
	struct vmcb_state *state;

	state = &vmcb->state;
	paging->cr3 = state->cr3;
	paging->cpl = svm_cpl(state);
	paging->cpu_mode = svm_vcpu_mode(vmcb);
	paging->paging_mode = svm_paging_mode(state->cr0, state->cr4,
	    state->efer);
}