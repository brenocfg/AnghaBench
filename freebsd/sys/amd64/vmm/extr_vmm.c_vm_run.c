#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct vm_run {int cpuid; int /*<<< orphan*/  vm_exit; } ;
struct TYPE_8__ {int rflags; } ;
struct TYPE_7__ {int /*<<< orphan*/  vector; } ;
struct TYPE_9__ {TYPE_2__ hlt; TYPE_1__ ioapic_eoi; } ;
struct vm_exit {int exitcode; TYPE_3__ u; scalar_t__ inst_length; scalar_t__ rip; } ;
struct vm_eventinfo {int /*<<< orphan*/ * iptr; int /*<<< orphan*/ * sptr; int /*<<< orphan*/ * rptr; } ;
struct vm {int maxcpus; int /*<<< orphan*/  cookie; int /*<<< orphan*/  suspend; int /*<<< orphan*/  rendezvous_func; struct vcpu* vcpu; int /*<<< orphan*/  vmspace; int /*<<< orphan*/  suspended_cpus; int /*<<< orphan*/  active_cpus; } ;
struct vcpu {scalar_t__ nextrip; int /*<<< orphan*/  reqidle; struct vm_exit exitinfo; } ;
struct pcb {int dummy; } ;
typedef  TYPE_4__* pmap_t ;
struct TYPE_10__ {int /*<<< orphan*/  pm_active; } ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 struct pcb* PCPU_GET (int /*<<< orphan*/ ) ; 
 int PSL_I ; 
 int /*<<< orphan*/  VCPU_CTR2 (struct vm*,int,char*,int,int) ; 
 int /*<<< orphan*/  VCPU_FROZEN ; 
 int /*<<< orphan*/  VCPU_RUNNING ; 
 int /*<<< orphan*/  VCPU_TOTAL_RUNTIME ; 
 int VMRUN (int /*<<< orphan*/ ,int,scalar_t__,TYPE_4__*,struct vm_eventinfo*) ; 
#define  VM_EXITCODE_HLT 139 
#define  VM_EXITCODE_INOUT 138 
#define  VM_EXITCODE_INOUT_STR 137 
#define  VM_EXITCODE_INST_EMUL 136 
#define  VM_EXITCODE_IOAPIC_EOI 135 
#define  VM_EXITCODE_MONITOR 134 
#define  VM_EXITCODE_MWAIT 133 
#define  VM_EXITCODE_PAGING 132 
#define  VM_EXITCODE_RENDEZVOUS 131 
#define  VM_EXITCODE_REQIDLE 130 
#define  VM_EXITCODE_SUSPENDED 129 
#define  VM_EXITCODE_VMINSN 128 
 int /*<<< orphan*/  bcopy (struct vm_exit*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int curcpu ; 
 int /*<<< orphan*/  curpcb ; 
 scalar_t__ rdtsc () ; 
 int /*<<< orphan*/  restore_guest_fpustate (struct vcpu*) ; 
 int /*<<< orphan*/  save_guest_fpustate (struct vcpu*) ; 
 int /*<<< orphan*/  set_pcb_flags (struct pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_require_state (struct vm*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vioapic_process_eoi (struct vm*,int,int /*<<< orphan*/ ) ; 
 int vm_handle_hlt (struct vm*,int,int,int*) ; 
 int vm_handle_inout (struct vm*,int,struct vm_exit*,int*) ; 
 int vm_handle_inst_emul (struct vm*,int,int*) ; 
 int vm_handle_paging (struct vm*,int,int*) ; 
 int /*<<< orphan*/  vm_handle_rendezvous (struct vm*,int) ; 
 int vm_handle_reqidle (struct vm*,int,int*) ; 
 int vm_handle_suspend (struct vm*,int,int*) ; 
 int /*<<< orphan*/  vm_inject_ud (struct vm*,int) ; 
 int /*<<< orphan*/  vmm_stat_incr (struct vm*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* vmspace_pmap (int /*<<< orphan*/ ) ; 

int
vm_run(struct vm *vm, struct vm_run *vmrun)
{
	struct vm_eventinfo evinfo;
	int error, vcpuid;
	struct vcpu *vcpu;
	struct pcb *pcb;
	uint64_t tscval;
	struct vm_exit *vme;
	bool retu, intr_disabled;
	pmap_t pmap;

	vcpuid = vmrun->cpuid;

	if (vcpuid < 0 || vcpuid >= vm->maxcpus)
		return (EINVAL);

	if (!CPU_ISSET(vcpuid, &vm->active_cpus))
		return (EINVAL);

	if (CPU_ISSET(vcpuid, &vm->suspended_cpus))
		return (EINVAL);

	pmap = vmspace_pmap(vm->vmspace);
	vcpu = &vm->vcpu[vcpuid];
	vme = &vcpu->exitinfo;
	evinfo.rptr = &vm->rendezvous_func;
	evinfo.sptr = &vm->suspend;
	evinfo.iptr = &vcpu->reqidle;
restart:
	critical_enter();

	KASSERT(!CPU_ISSET(curcpu, &pmap->pm_active),
	    ("vm_run: absurd pm_active"));

	tscval = rdtsc();

	pcb = PCPU_GET(curpcb);
	set_pcb_flags(pcb, PCB_FULL_IRET);

	restore_guest_fpustate(vcpu);

	vcpu_require_state(vm, vcpuid, VCPU_RUNNING);
	error = VMRUN(vm->cookie, vcpuid, vcpu->nextrip, pmap, &evinfo);
	vcpu_require_state(vm, vcpuid, VCPU_FROZEN);

	save_guest_fpustate(vcpu);

	vmm_stat_incr(vm, vcpuid, VCPU_TOTAL_RUNTIME, rdtsc() - tscval);

	critical_exit();

	if (error == 0) {
		retu = false;
		vcpu->nextrip = vme->rip + vme->inst_length;
		switch (vme->exitcode) {
		case VM_EXITCODE_REQIDLE:
			error = vm_handle_reqidle(vm, vcpuid, &retu);
			break;
		case VM_EXITCODE_SUSPENDED:
			error = vm_handle_suspend(vm, vcpuid, &retu);
			break;
		case VM_EXITCODE_IOAPIC_EOI:
			vioapic_process_eoi(vm, vcpuid,
			    vme->u.ioapic_eoi.vector);
			break;
		case VM_EXITCODE_RENDEZVOUS:
			vm_handle_rendezvous(vm, vcpuid);
			error = 0;
			break;
		case VM_EXITCODE_HLT:
			intr_disabled = ((vme->u.hlt.rflags & PSL_I) == 0);
			error = vm_handle_hlt(vm, vcpuid, intr_disabled, &retu);
			break;
		case VM_EXITCODE_PAGING:
			error = vm_handle_paging(vm, vcpuid, &retu);
			break;
		case VM_EXITCODE_INST_EMUL:
			error = vm_handle_inst_emul(vm, vcpuid, &retu);
			break;
		case VM_EXITCODE_INOUT:
		case VM_EXITCODE_INOUT_STR:
			error = vm_handle_inout(vm, vcpuid, vme, &retu);
			break;
		case VM_EXITCODE_MONITOR:
		case VM_EXITCODE_MWAIT:
		case VM_EXITCODE_VMINSN:
			vm_inject_ud(vm, vcpuid);
			break;
		default:
			retu = true;	/* handled in userland */
			break;
		}
	}

	if (error == 0 && retu == false)
		goto restart;

	VCPU_CTR2(vm, vcpuid, "retu %d/%d", error, vme->exitcode);

	/* copy the exit information */
	bcopy(vme, &vmrun->vm_exit, sizeof(struct vm_exit));
	return (error);
}