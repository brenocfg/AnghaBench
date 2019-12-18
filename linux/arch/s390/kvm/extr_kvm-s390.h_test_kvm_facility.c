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
struct TYPE_3__ {int /*<<< orphan*/  fac_list; int /*<<< orphan*/  fac_mask; } ;
struct TYPE_4__ {TYPE_1__ model; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 scalar_t__ __test_facility (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int test_kvm_facility(struct kvm *kvm, unsigned long nr)
{
	return __test_facility(nr, kvm->arch.model.fac_mask) &&
		__test_facility(nr, kvm->arch.model.fac_list);
}