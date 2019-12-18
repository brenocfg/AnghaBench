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
typedef  int u64 ;
typedef  int gfn_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int shadow_nonpresent_or_rsvd_lower_gfn_mask ; 
 int shadow_nonpresent_or_rsvd_mask ; 
 int shadow_nonpresent_or_rsvd_mask_len ; 

__attribute__((used)) static gfn_t get_mmio_spte_gfn(u64 spte)
{
	u64 gpa = spte & shadow_nonpresent_or_rsvd_lower_gfn_mask;

	gpa |= (spte >> shadow_nonpresent_or_rsvd_mask_len)
	       & shadow_nonpresent_or_rsvd_mask;

	return gpa >> PAGE_SHIFT;
}