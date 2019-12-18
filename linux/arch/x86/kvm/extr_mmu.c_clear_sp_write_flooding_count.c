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
struct kvm_mmu_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_sp_write_flooding_count (struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_sp_write_flooding_count(u64 *spte)
{
	struct kvm_mmu_page *sp =  page_header(__pa(spte));

	__clear_sp_write_flooding_count(sp);
}