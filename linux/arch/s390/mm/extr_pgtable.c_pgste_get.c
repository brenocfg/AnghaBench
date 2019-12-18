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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgste_t ;

/* Variables and functions */
 int PTRS_PER_PTE ; 
 int /*<<< orphan*/  __pgste (unsigned long) ; 

__attribute__((used)) static inline pgste_t pgste_get(pte_t *ptep)
{
	unsigned long pgste = 0;
#ifdef CONFIG_PGSTE
	pgste = *(unsigned long *)(ptep + PTRS_PER_PTE);
#endif
	return __pgste(pgste);
}