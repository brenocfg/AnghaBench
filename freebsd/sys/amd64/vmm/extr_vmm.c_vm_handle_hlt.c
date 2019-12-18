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
struct vm {int /*<<< orphan*/  halted_cpus; int /*<<< orphan*/  active_cpus; scalar_t__ suspend; int /*<<< orphan*/ * rendezvous_func; struct vcpu* vcpu; } ;
struct vcpu {int /*<<< orphan*/  mtx; int /*<<< orphan*/  vlapic; scalar_t__ reqidle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR_ATOMIC (int,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VCPU_CTR0 (struct vm*,int,char*) ; 
 int /*<<< orphan*/  VCPU_FROZEN ; 
 int /*<<< orphan*/  VCPU_IDLE_TICKS ; 
 int /*<<< orphan*/  VCPU_SLEEPING ; 
 int /*<<< orphan*/  VM_SUSPEND_HALT ; 
 scalar_t__ halt_detection_enabled ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep_spin (struct vcpu*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int ticks ; 
 scalar_t__ vcpu_debugged (struct vm*,int) ; 
 int /*<<< orphan*/  vcpu_lock (struct vcpu*) ; 
 int /*<<< orphan*/  vcpu_require_state_locked (struct vm*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vcpu_should_yield (struct vm*,int) ; 
 int /*<<< orphan*/  vcpu_unlock (struct vcpu*) ; 
 scalar_t__ vlapic_pending_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vm_extint_pending (struct vm*,int) ; 
 scalar_t__ vm_nmi_pending (struct vm*,int) ; 
 int /*<<< orphan*/  vm_suspend (struct vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_incr (struct vm*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vm_handle_hlt(struct vm *vm, int vcpuid, bool intr_disabled, bool *retu)
{
	struct vcpu *vcpu;
	const char *wmesg;
	int t, vcpu_halted, vm_halted;

	KASSERT(!CPU_ISSET(vcpuid, &vm->halted_cpus), ("vcpu already halted"));

	vcpu = &vm->vcpu[vcpuid];
	vcpu_halted = 0;
	vm_halted = 0;

	vcpu_lock(vcpu);
	while (1) {
		/*
		 * Do a final check for pending NMI or interrupts before
		 * really putting this thread to sleep. Also check for
		 * software events that would cause this vcpu to wakeup.
		 *
		 * These interrupts/events could have happened after the
		 * vcpu returned from VMRUN() and before it acquired the
		 * vcpu lock above.
		 */
		if (vm->rendezvous_func != NULL || vm->suspend || vcpu->reqidle)
			break;
		if (vm_nmi_pending(vm, vcpuid))
			break;
		if (!intr_disabled) {
			if (vm_extint_pending(vm, vcpuid) ||
			    vlapic_pending_intr(vcpu->vlapic, NULL)) {
				break;
			}
		}

		/* Don't go to sleep if the vcpu thread needs to yield */
		if (vcpu_should_yield(vm, vcpuid))
			break;

		if (vcpu_debugged(vm, vcpuid))
			break;

		/*
		 * Some Linux guests implement "halt" by having all vcpus
		 * execute HLT with interrupts disabled. 'halted_cpus' keeps
		 * track of the vcpus that have entered this state. When all
		 * vcpus enter the halted state the virtual machine is halted.
		 */
		if (intr_disabled) {
			wmesg = "vmhalt";
			VCPU_CTR0(vm, vcpuid, "Halted");
			if (!vcpu_halted && halt_detection_enabled) {
				vcpu_halted = 1;
				CPU_SET_ATOMIC(vcpuid, &vm->halted_cpus);
			}
			if (CPU_CMP(&vm->halted_cpus, &vm->active_cpus) == 0) {
				vm_halted = 1;
				break;
			}
		} else {
			wmesg = "vmidle";
		}

		t = ticks;
		vcpu_require_state_locked(vm, vcpuid, VCPU_SLEEPING);
		/*
		 * XXX msleep_spin() cannot be interrupted by signals so
		 * wake up periodically to check pending signals.
		 */
		msleep_spin(vcpu, &vcpu->mtx, wmesg, hz);
		vcpu_require_state_locked(vm, vcpuid, VCPU_FROZEN);
		vmm_stat_incr(vm, vcpuid, VCPU_IDLE_TICKS, ticks - t);
	}

	if (vcpu_halted)
		CPU_CLR_ATOMIC(vcpuid, &vm->halted_cpus);

	vcpu_unlock(vcpu);

	if (vm_halted)
		vm_suspend(vm, VM_SUSPEND_HALT);

	return (0);
}