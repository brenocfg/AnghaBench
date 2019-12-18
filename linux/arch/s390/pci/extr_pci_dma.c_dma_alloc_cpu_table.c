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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int ZPCI_TABLE_ENTRIES ; 
 unsigned long ZPCI_TABLE_INVALID ; 
 int /*<<< orphan*/  dma_region_table_cache ; 
 unsigned long* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned long *dma_alloc_cpu_table(void)
{
	unsigned long *table, *entry;

	table = kmem_cache_alloc(dma_region_table_cache, GFP_ATOMIC);
	if (!table)
		return NULL;

	for (entry = table; entry < table + ZPCI_TABLE_ENTRIES; entry++)
		*entry = ZPCI_TABLE_INVALID;
	return table;
}