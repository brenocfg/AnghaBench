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
struct kvm_vcpu_hv_synic {int /*<<< orphan*/  auto_eoi_bitmap; int /*<<< orphan*/  vec_bitmap; } ;

/* Variables and functions */
 int HV_SYNIC_FIRST_VALID_VECTOR ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ synic_has_vector_auto_eoi (struct kvm_vcpu_hv_synic*,int) ; 
 scalar_t__ synic_has_vector_connected (struct kvm_vcpu_hv_synic*,int) ; 

__attribute__((used)) static void synic_update_vector(struct kvm_vcpu_hv_synic *synic,
				int vector)
{
	if (vector < HV_SYNIC_FIRST_VALID_VECTOR)
		return;

	if (synic_has_vector_connected(synic, vector))
		__set_bit(vector, synic->vec_bitmap);
	else
		__clear_bit(vector, synic->vec_bitmap);

	if (synic_has_vector_auto_eoi(synic, vector))
		__set_bit(vector, synic->auto_eoi_bitmap);
	else
		__clear_bit(vector, synic->auto_eoi_bitmap);
}