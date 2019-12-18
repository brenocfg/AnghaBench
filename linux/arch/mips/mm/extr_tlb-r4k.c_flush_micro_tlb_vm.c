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
 int VM_EXEC ; 
 int /*<<< orphan*/  flush_micro_tlb () ; 

__attribute__((used)) static inline void flush_micro_tlb_vm(struct vm_area_struct *vma)
{
	if (vma->vm_flags & VM_EXEC)
		flush_micro_tlb();
}