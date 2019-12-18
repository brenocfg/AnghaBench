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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_mmu {int /*<<< orphan*/  shadow_zero_check; } ;

/* Variables and functions */
 int __is_rsvd_bits_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool is_shadow_zero_bits_set(struct kvm_mmu *mmu, u64 spte, int level)
{
	return __is_rsvd_bits_set(&mmu->shadow_zero_check, spte, level);
}