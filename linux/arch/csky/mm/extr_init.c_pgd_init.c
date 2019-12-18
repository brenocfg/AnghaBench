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

/* Variables and functions */
 int PTRS_PER_PGD ; 
 unsigned long __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalid_pte_table ; 

void pgd_init(unsigned long *p)
{
	int i;

	for (i = 0; i < PTRS_PER_PGD; i++)
		p[i] = __pa(invalid_pte_table);
}