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
struct TYPE_2__ {int nested_enable; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested ; 
 scalar_t__ no_mixing_hpt_and_radix ; 

__attribute__((used)) static int kvmhv_enable_nested(struct kvm *kvm)
{
	if (!nested)
		return -EPERM;
	if (!cpu_has_feature(CPU_FTR_ARCH_300) || no_mixing_hpt_and_radix)
		return -ENODEV;

	/* kvm == NULL means the caller is testing if the capability exists */
	if (kvm)
		kvm->arch.nested_enable = true;
	return 0;
}