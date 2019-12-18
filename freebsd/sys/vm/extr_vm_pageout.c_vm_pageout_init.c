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
typedef  int u_int ;
struct vm_domain {scalar_t__ vmd_free_count; scalar_t__ vmd_free_severe; scalar_t__ vmd_interrupt_free_min; scalar_t__ vmd_pageout_free_min; scalar_t__ vmd_inactive_target; scalar_t__ vmd_free_min; scalar_t__ vmd_free_target; scalar_t__ vmd_free_reserved; } ;
struct TYPE_2__ {int v_page_count; int /*<<< orphan*/  v_free_severe; int /*<<< orphan*/  v_interrupt_free_min; int /*<<< orphan*/  v_pageout_free_min; int /*<<< orphan*/  v_inactive_target; int /*<<< orphan*/  v_free_min; int /*<<< orphan*/  v_free_target; int /*<<< orphan*/  v_free_reserved; } ;

/* Variables and functions */
 struct vm_domain* VM_DOMAIN (int) ; 
 TYPE_1__ vm_cnt ; 
 int vm_ndomains ; 
 int vm_page_max_user_wired ; 
 int /*<<< orphan*/  vm_pageout_init_domain (int) ; 
 int vm_pageout_page_count ; 
 int vm_pageout_update_period ; 

__attribute__((used)) static void
vm_pageout_init(void)
{
	u_int freecount;
	int i;

	/*
	 * Initialize some paging parameters.
	 */
	if (vm_cnt.v_page_count < 2000)
		vm_pageout_page_count = 8;

	freecount = 0;
	for (i = 0; i < vm_ndomains; i++) {
		struct vm_domain *vmd;

		vm_pageout_init_domain(i);
		vmd = VM_DOMAIN(i);
		vm_cnt.v_free_reserved += vmd->vmd_free_reserved;
		vm_cnt.v_free_target += vmd->vmd_free_target;
		vm_cnt.v_free_min += vmd->vmd_free_min;
		vm_cnt.v_inactive_target += vmd->vmd_inactive_target;
		vm_cnt.v_pageout_free_min += vmd->vmd_pageout_free_min;
		vm_cnt.v_interrupt_free_min += vmd->vmd_interrupt_free_min;
		vm_cnt.v_free_severe += vmd->vmd_free_severe;
		freecount += vmd->vmd_free_count;
	}

	/*
	 * Set interval in seconds for active scan.  We want to visit each
	 * page at least once every ten minutes.  This is to prevent worst
	 * case paging behaviors with stale active LRU.
	 */
	if (vm_pageout_update_period == 0)
		vm_pageout_update_period = 600;

	if (vm_page_max_user_wired == 0)
		vm_page_max_user_wired = freecount / 3;
}