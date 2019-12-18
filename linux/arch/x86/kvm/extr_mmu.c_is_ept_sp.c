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
struct TYPE_2__ {scalar_t__ smap_andnot_wp; scalar_t__ cr0_wp; } ;
struct kvm_mmu_page {TYPE_1__ role; } ;

/* Variables and functions */

__attribute__((used)) static inline bool is_ept_sp(struct kvm_mmu_page *sp)
{
	return sp->role.cr0_wp && sp->role.smap_andnot_wp;
}