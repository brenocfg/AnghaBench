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
 scalar_t__ PGD_INDEX_SIZE ; 
 scalar_t__ PMD_CACHE_INDEX ; 
 scalar_t__ PUD_CACHE_INDEX ; 
 int /*<<< orphan*/  pgtable_cache_add (scalar_t__) ; 

void pgtable_cache_init(void)
{
	pgtable_cache_add(PGD_INDEX_SIZE);

	if (PMD_CACHE_INDEX)
		pgtable_cache_add(PMD_CACHE_INDEX);
	/*
	 * In all current configs, when the PUD index exists it's the
	 * same size as either the pgd or pmd index except with THP enabled
	 * on book3s 64
	 */
	if (PUD_CACHE_INDEX)
		pgtable_cache_add(PUD_CACHE_INDEX);
}