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
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int handle_page_fault (unsigned long,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * virt_to_pte (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static pte_t *maybe_map(unsigned long virt, int is_write)
{
	pte_t *pte = virt_to_pte(current->mm, virt);
	int err, dummy_code;

	if ((pte == NULL) || !pte_present(*pte) ||
	    (is_write && !pte_write(*pte))) {
		err = handle_page_fault(virt, 0, is_write, 1, &dummy_code);
		if (err)
			return NULL;
		pte = virt_to_pte(current->mm, virt);
	}
	if (!pte_present(*pte))
		pte = NULL;

	return pte;
}