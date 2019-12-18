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
struct vm {int maxcpus; int /*<<< orphan*/  cookie; struct vcpu* vcpu; } ;
struct vcpu {int /*<<< orphan*/  stats; int /*<<< orphan*/  guestfpu; int /*<<< orphan*/  guest_xcr0; scalar_t__ exception_pending; scalar_t__ extint_pending; scalar_t__ nmi_pending; scalar_t__ exitintinfo; scalar_t__ reqidle; int /*<<< orphan*/  vlapic; int /*<<< orphan*/  hostcpu; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  NOCPU ; 
 int /*<<< orphan*/  VCPU_IDLE ; 
 int /*<<< orphan*/  VLAPIC_INIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  X2APIC_DISABLED ; 
 int /*<<< orphan*/  XFEATURE_ENABLED_X87 ; 
 int /*<<< orphan*/  fpu_save_area_alloc () ; 
 int /*<<< orphan*/  fpu_save_area_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_lock_init (struct vcpu*) ; 
 int /*<<< orphan*/  vcpu_lock_initialized (struct vcpu*) ; 
 int /*<<< orphan*/  vm_set_x2apic_state (struct vm*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_alloc () ; 
 int /*<<< orphan*/  vmm_stat_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vcpu_init(struct vm *vm, int vcpu_id, bool create)
{
	struct vcpu *vcpu;

	KASSERT(vcpu_id >= 0 && vcpu_id < vm->maxcpus,
	    ("vcpu_init: invalid vcpu %d", vcpu_id));
	  
	vcpu = &vm->vcpu[vcpu_id];

	if (create) {
		KASSERT(!vcpu_lock_initialized(vcpu), ("vcpu %d already "
		    "initialized", vcpu_id));
		vcpu_lock_init(vcpu);
		vcpu->state = VCPU_IDLE;
		vcpu->hostcpu = NOCPU;
		vcpu->guestfpu = fpu_save_area_alloc();
		vcpu->stats = vmm_stat_alloc();
	}

	vcpu->vlapic = VLAPIC_INIT(vm->cookie, vcpu_id);
	vm_set_x2apic_state(vm, vcpu_id, X2APIC_DISABLED);
	vcpu->reqidle = 0;
	vcpu->exitintinfo = 0;
	vcpu->nmi_pending = 0;
	vcpu->extint_pending = 0;
	vcpu->exception_pending = 0;
	vcpu->guest_xcr0 = XFEATURE_ENABLED_X87;
	fpu_save_area_reset(vcpu->guestfpu);
	vmm_stat_init(vcpu->stats);
}