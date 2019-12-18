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
struct TYPE_3__ {int nr_hw_wp; struct kvm_hw_wp_info_arch* hw_wp_info; } ;
struct TYPE_4__ {TYPE_1__ guestdbg; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm_hw_wp_info_arch {int /*<<< orphan*/  len; int /*<<< orphan*/  old_data; int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_guest_abs (struct kvm_vcpu*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kvm_hw_wp_info_arch *any_wp_changed(struct kvm_vcpu *vcpu)
{
	int i;
	struct kvm_hw_wp_info_arch *wp_info = NULL;
	void *temp = NULL;

	if (vcpu->arch.guestdbg.nr_hw_wp == 0)
		return NULL;

	for (i = 0; i < vcpu->arch.guestdbg.nr_hw_wp; i++) {
		wp_info = &vcpu->arch.guestdbg.hw_wp_info[i];
		if (!wp_info || !wp_info->old_data || wp_info->len <= 0)
			continue;

		temp = kmalloc(wp_info->len, GFP_KERNEL);
		if (!temp)
			continue;

		/* refetch the wp data and compare it to the old value */
		if (!read_guest_abs(vcpu, wp_info->phys_addr, temp,
				    wp_info->len)) {
			if (memcmp(temp, wp_info->old_data, wp_info->len)) {
				kfree(temp);
				return wp_info;
			}
		}
		kfree(temp);
		temp = NULL;
	}

	return NULL;
}