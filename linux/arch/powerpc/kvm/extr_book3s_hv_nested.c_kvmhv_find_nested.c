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
struct kvm_nested_guest {int dummy; } ;
struct TYPE_2__ {int max_nested_lpid; struct kvm_nested_guest** nested_guests; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */

__attribute__((used)) static struct kvm_nested_guest *kvmhv_find_nested(struct kvm *kvm, int lpid)
{
	if (lpid > kvm->arch.max_nested_lpid)
		return NULL;
	return kvm->arch.nested_guests[lpid];
}