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
struct vm {int maxcpus; int /*<<< orphan*/  suspended_cpus; scalar_t__ suspend; int /*<<< orphan*/  debug_cpus; int /*<<< orphan*/  active_cpus; int /*<<< orphan*/  vrtc; int /*<<< orphan*/  vpmtmr; int /*<<< orphan*/  vatpit; int /*<<< orphan*/  vatpic; int /*<<< orphan*/  vhpet; int /*<<< orphan*/  vioapic; int /*<<< orphan*/ * iommu; int /*<<< orphan*/  vmspace; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VMINIT (struct vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vatpic_init (struct vm*) ; 
 int /*<<< orphan*/  vatpit_init (struct vm*) ; 
 int /*<<< orphan*/  vcpu_init (struct vm*,int,int) ; 
 int /*<<< orphan*/  vhpet_init (struct vm*) ; 
 int /*<<< orphan*/  vioapic_init (struct vm*) ; 
 int /*<<< orphan*/  vmspace_pmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpmtmr_init (struct vm*) ; 
 int /*<<< orphan*/  vrtc_init (struct vm*) ; 

__attribute__((used)) static void
vm_init(struct vm *vm, bool create)
{
	int i;

	vm->cookie = VMINIT(vm, vmspace_pmap(vm->vmspace));
	vm->iommu = NULL;
	vm->vioapic = vioapic_init(vm);
	vm->vhpet = vhpet_init(vm);
	vm->vatpic = vatpic_init(vm);
	vm->vatpit = vatpit_init(vm);
	vm->vpmtmr = vpmtmr_init(vm);
	if (create)
		vm->vrtc = vrtc_init(vm);

	CPU_ZERO(&vm->active_cpus);
	CPU_ZERO(&vm->debug_cpus);

	vm->suspend = 0;
	CPU_ZERO(&vm->suspended_cpus);

	for (i = 0; i < vm->maxcpus; i++)
		vcpu_init(vm, i, create);
}