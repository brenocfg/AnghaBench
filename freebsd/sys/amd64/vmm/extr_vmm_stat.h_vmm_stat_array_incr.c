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
typedef  scalar_t__ uint64_t ;
struct vmm_stat_type {int index; int nelems; } ;
struct vm {int dummy; } ;

/* Variables and functions */
 scalar_t__* vcpu_stats (struct vm*,int) ; 

__attribute__((used)) static void __inline
vmm_stat_array_incr(struct vm *vm, int vcpu, struct vmm_stat_type *vst,
		    int statidx, uint64_t x)
{
#ifdef VMM_KEEP_STATS
	uint64_t *stats;
	
	stats = vcpu_stats(vm, vcpu);

	if (vst->index >= 0 && statidx < vst->nelems)
		stats[vst->index + statidx] += x;
#endif
}