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
struct vm_area_struct {int vm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  R4K_INDEX ; 
 int VM_EXEC ; 
 scalar_t__ cpu_has_dc_aliases ; 
 int /*<<< orphan*/  local_r4k_flush_cache_range ; 
 int /*<<< orphan*/  r4k_on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static void r4k_flush_cache_range(struct vm_area_struct *vma,
	unsigned long start, unsigned long end)
{
	int exec = vma->vm_flags & VM_EXEC;

	if (cpu_has_dc_aliases || exec)
		r4k_on_each_cpu(R4K_INDEX, local_r4k_flush_cache_range, vma);
}