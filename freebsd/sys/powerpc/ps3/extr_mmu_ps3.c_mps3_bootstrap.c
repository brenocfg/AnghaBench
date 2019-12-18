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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint64_t ;
struct lpteg {int dummy; } ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  lv1_construct_virtual_address_space (int,int,unsigned long,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lv1_destruct_virtual_address_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_select_virtual_address_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_early_bootstrap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_late_bootstrap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_mid_bootstrap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int moea64_pteg_count ; 
 int /*<<< orphan*/  mps3_table_lock ; 
 int /*<<< orphan*/  mps3_vas_id ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mps3_bootstrap(mmu_t mmup, vm_offset_t kernelstart, vm_offset_t kernelend)
{
	uint64_t final_pteg_count;

	mtx_init(&mps3_table_lock, "page table", NULL, MTX_DEF);

	moea64_early_bootstrap(mmup, kernelstart, kernelend);

	/* In case we had a page table already */
	lv1_destruct_virtual_address_space(0);

	/* Allocate new hardware page table */
	lv1_construct_virtual_address_space(
	    20 /* log_2(moea64_pteg_count) */, 2 /* n page sizes */,
	    (24UL << 56) | (16UL << 48) /* page sizes 16 MB + 64 KB */,
	    &mps3_vas_id, &final_pteg_count
	);

	lv1_select_virtual_address_space(mps3_vas_id);

	moea64_pteg_count = final_pteg_count / sizeof(struct lpteg);

	moea64_mid_bootstrap(mmup, kernelstart, kernelend);
	moea64_late_bootstrap(mmup, kernelstart, kernelend);
}