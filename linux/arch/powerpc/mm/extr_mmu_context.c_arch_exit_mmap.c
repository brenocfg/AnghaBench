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
struct mm_struct {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  pte_frag_destroy (void*) ; 
 void* pte_frag_get (int /*<<< orphan*/ *) ; 

void arch_exit_mmap(struct mm_struct *mm)
{
	void *frag = pte_frag_get(&mm->context);

	if (frag)
		pte_frag_destroy(frag);
}