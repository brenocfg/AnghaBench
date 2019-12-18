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
typedef  size_t u32 ;
struct kvm_vcpu_hv_synic {int /*<<< orphan*/ * sint_to_gsi; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct kvm_vcpu_hv_synic* synic_get (struct kvm*,size_t) ; 

__attribute__((used)) static int kvm_hv_set_sint_gsi(struct kvm *kvm, u32 vpidx, u32 sint, int gsi)
{
	struct kvm_vcpu_hv_synic *synic;

	synic = synic_get(kvm, vpidx);
	if (!synic)
		return -EINVAL;

	if (sint >= ARRAY_SIZE(synic->sint_to_gsi))
		return -EINVAL;

	atomic_set(&synic->sint_to_gsi[sint], gsi);
	return 0;
}