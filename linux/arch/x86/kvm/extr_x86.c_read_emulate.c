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
 int /*<<< orphan*/  kvm_vcpu_read_guest (struct kvm_vcpu*,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int read_emulate(struct kvm_vcpu *vcpu, gpa_t gpa,
			void *val, int bytes)
{
	return !kvm_vcpu_read_guest(vcpu, gpa, val, bytes);
}