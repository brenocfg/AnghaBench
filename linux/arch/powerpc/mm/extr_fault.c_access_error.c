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
 int /*<<< orphan*/  CPU_FTR_NOEXECUTE ; 
 int VM_EXEC ; 
 int VM_READ ; 
 int VM_WRITE ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool access_error(bool is_write, bool is_exec,
			 struct vm_area_struct *vma)
{
	/*
	 * Allow execution from readable areas if the MMU does not
	 * provide separate controls over reading and executing.
	 *
	 * Note: That code used to not be enabled for 4xx/BookE.
	 * It is now as I/D cache coherency for these is done at
	 * set_pte_at() time and I see no reason why the test
	 * below wouldn't be valid on those processors. This -may-
	 * break programs compiled with a really old ABI though.
	 */
	if (is_exec) {
		return !(vma->vm_flags & VM_EXEC) &&
			(cpu_has_feature(CPU_FTR_NOEXECUTE) ||
			 !(vma->vm_flags & (VM_READ | VM_WRITE)));
	}

	if (is_write) {
		if (unlikely(!(vma->vm_flags & VM_WRITE)))
			return true;
		return false;
	}

	if (unlikely(!(vma->vm_flags & (VM_READ | VM_EXEC | VM_WRITE))))
		return true;
	/*
	 * We should ideally do the vma pkey access check here. But in the
	 * fault path, handle_mm_fault() also does the same check. To avoid
	 * these multiple checks, we skip it here and handle access error due
	 * to pkeys later.
	 */
	return false;
}