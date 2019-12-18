#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* pmd_frag; void* pte_frag; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmd_frag_destroy (void*) ; 
 int /*<<< orphan*/  pte_frag_destroy (void*) ; 

__attribute__((used)) static void destroy_pagetable_cache(struct mm_struct *mm)
{
	void *frag;

	frag = mm->context.pte_frag;
	if (frag)
		pte_frag_destroy(frag);

	frag = mm->context.pmd_frag;
	if (frag)
		pmd_frag_destroy(frag);
	return;
}