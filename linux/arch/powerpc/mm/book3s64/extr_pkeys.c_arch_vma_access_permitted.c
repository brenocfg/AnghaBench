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
struct vm_area_struct {int dummy; } ;

/* Variables and functions */
 int pkey_access_permitted (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pkey_disabled ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 scalar_t__ vma_is_foreign (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_pkey (struct vm_area_struct*) ; 

bool arch_vma_access_permitted(struct vm_area_struct *vma, bool write,
			       bool execute, bool foreign)
{
	if (static_branch_likely(&pkey_disabled))
		return true;
	/*
	 * Do not enforce our key-permissions on a foreign vma.
	 */
	if (foreign || vma_is_foreign(vma))
		return true;

	return pkey_access_permitted(vma_pkey(vma), write, execute);
}