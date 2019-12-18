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
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_page_track_write (struct kvm_vcpu*,int /*<<< orphan*/ ,void const*,int) ; 
 int kvm_vcpu_write_guest (struct kvm_vcpu*,int /*<<< orphan*/ ,void const*,int) ; 

int emulator_write_phys(struct kvm_vcpu *vcpu, gpa_t gpa,
			const void *val, int bytes)
{
	int ret;

	ret = kvm_vcpu_write_guest(vcpu, gpa, val, bytes);
	if (ret < 0)
		return 0;
	kvm_page_track_write(vcpu, gpa, val, bytes);
	return 1;
}