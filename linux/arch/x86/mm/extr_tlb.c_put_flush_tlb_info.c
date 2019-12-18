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

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  flush_tlb_info_idx ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void put_flush_tlb_info(void)
{
#ifdef CONFIG_DEBUG_VM
	/* Complete reentrency prevention checks */
	barrier();
	this_cpu_dec(flush_tlb_info_idx);
#endif
}