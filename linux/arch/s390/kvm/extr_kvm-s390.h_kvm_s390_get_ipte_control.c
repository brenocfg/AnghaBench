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
typedef  union ipte_control {int dummy; } ipte_control ;
struct TYPE_2__ {struct bsca_block* sca; } ;
struct kvm {TYPE_1__ arch; } ;
struct bsca_block {union ipte_control ipte_control; } ;

/* Variables and functions */

__attribute__((used)) static inline union ipte_control *kvm_s390_get_ipte_control(struct kvm *kvm)
{
	struct bsca_block *sca = kvm->arch.sca; /* SCA version doesn't matter */

	return &sca->ipte_control;
}