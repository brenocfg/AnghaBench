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
typedef  enum slb_index { ____Placeholder_slb_index } slb_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert_slb_presence (int,unsigned long) ; 
 int /*<<< orphan*/  slb_shadow_update (unsigned long,int,unsigned long,int) ; 

__attribute__((used)) static inline void create_shadowed_slbe(unsigned long ea, int ssize,
					unsigned long flags,
					enum slb_index index)
{
	/*
	 * Updating the shadow buffer before writing the SLB ensures
	 * we don't get a stale entry here if we get preempted by PHYP
	 * between these two statements.
	 */
	slb_shadow_update(ea, ssize, flags, index);

	assert_slb_presence(false, ea);
	asm volatile("slbmte  %0,%1" :
		     : "r" (mk_vsid_data(ea, ssize, flags)),
		       "r" (mk_esid_data(ea, ssize, index))
		     : "memory" );
}