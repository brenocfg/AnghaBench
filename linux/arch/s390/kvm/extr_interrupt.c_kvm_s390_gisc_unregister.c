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
typedef  size_t u32 ;
struct TYPE_4__ {scalar_t__* ref_count; int mask; int /*<<< orphan*/  ref_lock; } ;
struct kvm_s390_gisa_interrupt {TYPE_2__ alert; int /*<<< orphan*/  origin; } ;
struct TYPE_3__ {struct kvm_s390_gisa_interrupt gisa_int; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ERANGE ; 
 size_t MAX_ISC ; 
 int /*<<< orphan*/  gisa_set_iam (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int kvm_s390_gisc_unregister(struct kvm *kvm, u32 gisc)
{
	struct kvm_s390_gisa_interrupt *gi = &kvm->arch.gisa_int;
	int rc = 0;

	if (!gi->origin)
		return -ENODEV;
	if (gisc > MAX_ISC)
		return -ERANGE;

	spin_lock(&gi->alert.ref_lock);
	if (gi->alert.ref_count[gisc] == 0) {
		rc = -EINVAL;
		goto out;
	}
	gi->alert.ref_count[gisc]--;
	if (gi->alert.ref_count[gisc] == 0) {
		gi->alert.mask &= ~(0x80 >> gisc);
		gisa_set_iam(gi->origin, gi->alert.mask);
	}
out:
	spin_unlock(&gi->alert.ref_lock);

	return rc;
}