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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 int PROT_EXEC ; 
 int execute_only_pkey (int /*<<< orphan*/ ) ; 
 scalar_t__ vma_is_pkey_exec_only (struct vm_area_struct*) ; 
 int vma_pkey (struct vm_area_struct*) ; 

int __arch_override_mprotect_pkey(struct vm_area_struct *vma, int prot,
				  int pkey)
{
	/*
	 * If the currently associated pkey is execute-only, but the requested
	 * protection is not execute-only, move it back to the default pkey.
	 */
	if (vma_is_pkey_exec_only(vma) && (prot != PROT_EXEC))
		return 0;

	/*
	 * The requested protection is execute-only. Hence let's use an
	 * execute-only pkey.
	 */
	if (prot == PROT_EXEC) {
		pkey = execute_only_pkey(vma->vm_mm);
		if (pkey > 0)
			return pkey;
	}

	/* Nothing to override. */
	return vma_pkey(vma);
}