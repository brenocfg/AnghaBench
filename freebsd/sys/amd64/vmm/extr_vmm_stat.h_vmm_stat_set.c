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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmm_stat_type {int dummy; } ;
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmm_stat_array_set (struct vm*,int,struct vmm_stat_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __inline
vmm_stat_set(struct vm *vm, int vcpu, struct vmm_stat_type *vst, uint64_t val)
{

#ifdef VMM_KEEP_STATS
	vmm_stat_array_set(vm, vcpu, vst, 0, val);
#endif
}