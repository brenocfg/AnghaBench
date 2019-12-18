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
struct vm {struct vcpu* vcpu; } ;
struct vcpu {int state; int reqidle; scalar_t__ hostcpu; int /*<<< orphan*/  mtx; } ;
typedef  enum vcpu_state { ____Placeholder_vcpu_state } vcpu_state ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NOCPU ; 
 int /*<<< orphan*/  VCPU_CTR1 (struct vm*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCPU_CTR2 (struct vm*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  VCPU_FROZEN 131 
#define  VCPU_IDLE 130 
#define  VCPU_RUNNING 129 
#define  VCPU_SLEEPING 128 
 scalar_t__ curcpu ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep_spin (int*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_assert_locked (struct vcpu*) ; 
 int /*<<< orphan*/  vcpu_notify_event_locked (struct vcpu*,int) ; 
 int /*<<< orphan*/  vcpu_state2str (int) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static int
vcpu_set_state_locked(struct vm *vm, int vcpuid, enum vcpu_state newstate,
    bool from_idle)
{
	struct vcpu *vcpu;
	int error;

	vcpu = &vm->vcpu[vcpuid];
	vcpu_assert_locked(vcpu);

	/*
	 * State transitions from the vmmdev_ioctl() must always begin from
	 * the VCPU_IDLE state. This guarantees that there is only a single
	 * ioctl() operating on a vcpu at any point.
	 */
	if (from_idle) {
		while (vcpu->state != VCPU_IDLE) {
			vcpu->reqidle = 1;
			vcpu_notify_event_locked(vcpu, false);
			VCPU_CTR1(vm, vcpuid, "vcpu state change from %s to "
			    "idle requested", vcpu_state2str(vcpu->state));
			msleep_spin(&vcpu->state, &vcpu->mtx, "vmstat", hz);
		}
	} else {
		KASSERT(vcpu->state != VCPU_IDLE, ("invalid transition from "
		    "vcpu idle state"));
	}

	if (vcpu->state == VCPU_RUNNING) {
		KASSERT(vcpu->hostcpu == curcpu, ("curcpu %d and hostcpu %d "
		    "mismatch for running vcpu", curcpu, vcpu->hostcpu));
	} else {
		KASSERT(vcpu->hostcpu == NOCPU, ("Invalid hostcpu %d for a "
		    "vcpu that is not running", vcpu->hostcpu));
	}

	/*
	 * The following state transitions are allowed:
	 * IDLE -> FROZEN -> IDLE
	 * FROZEN -> RUNNING -> FROZEN
	 * FROZEN -> SLEEPING -> FROZEN
	 */
	switch (vcpu->state) {
	case VCPU_IDLE:
	case VCPU_RUNNING:
	case VCPU_SLEEPING:
		error = (newstate != VCPU_FROZEN);
		break;
	case VCPU_FROZEN:
		error = (newstate == VCPU_FROZEN);
		break;
	default:
		error = 1;
		break;
	}

	if (error)
		return (EBUSY);

	VCPU_CTR2(vm, vcpuid, "vcpu state changed from %s to %s",
	    vcpu_state2str(vcpu->state), vcpu_state2str(newstate));

	vcpu->state = newstate;
	if (newstate == VCPU_RUNNING)
		vcpu->hostcpu = curcpu;
	else
		vcpu->hostcpu = NOCPU;

	if (newstate == VCPU_IDLE)
		wakeup(&vcpu->state);

	return (0);
}