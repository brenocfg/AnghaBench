#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s390_io_adapter {int /*<<< orphan*/  isc; int /*<<< orphan*/  id; int /*<<< orphan*/  suppressible; } ;
struct kvm_s390_interrupt {int /*<<< orphan*/  parm64; int /*<<< orphan*/  parm; int /*<<< orphan*/  type; } ;
struct kvm_s390_float_interrupt {int nimm; int simm; int /*<<< orphan*/  ais_lock; } ;
struct TYPE_2__ {struct kvm_s390_float_interrupt float_int; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int AIS_MODE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KVM_S390_AIS_MODE_SINGLE ; 
 int /*<<< orphan*/  KVM_S390_INT_IO (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_to_int_word (int /*<<< orphan*/ ) ; 
 int kvm_s390_inject_vm (struct kvm*,struct kvm_s390_interrupt*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_kvm_facility (struct kvm*,int) ; 
 int /*<<< orphan*/  trace_kvm_s390_airq_suppressed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_s390_modify_ais_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kvm_s390_inject_airq(struct kvm *kvm,
				struct s390_io_adapter *adapter)
{
	struct kvm_s390_float_interrupt *fi = &kvm->arch.float_int;
	struct kvm_s390_interrupt s390int = {
		.type = KVM_S390_INT_IO(1, 0, 0, 0),
		.parm = 0,
		.parm64 = isc_to_int_word(adapter->isc),
	};
	int ret = 0;

	if (!test_kvm_facility(kvm, 72) || !adapter->suppressible)
		return kvm_s390_inject_vm(kvm, &s390int);

	mutex_lock(&fi->ais_lock);
	if (fi->nimm & AIS_MODE_MASK(adapter->isc)) {
		trace_kvm_s390_airq_suppressed(adapter->id, adapter->isc);
		goto out;
	}

	ret = kvm_s390_inject_vm(kvm, &s390int);
	if (!ret && (fi->simm & AIS_MODE_MASK(adapter->isc))) {
		fi->nimm |= AIS_MODE_MASK(adapter->isc);
		trace_kvm_s390_modify_ais_mode(adapter->isc,
					       KVM_S390_AIS_MODE_SINGLE, 2);
	}
out:
	mutex_unlock(&fi->ais_lock);
	return ret;
}