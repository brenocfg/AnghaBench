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
 int ZPCI_TABLE_ENTRIES ; 
 int /*<<< orphan*/  dma_free_cpu_table (unsigned long*) ; 
 int /*<<< orphan*/  dma_free_page_table (int /*<<< orphan*/ ) ; 
 unsigned long* get_rt_sto (unsigned long) ; 
 int /*<<< orphan*/  get_st_pto (unsigned long) ; 
 scalar_t__ reg_entry_isvalid (unsigned long) ; 

void dma_free_seg_table(unsigned long entry)
{
	unsigned long *sto = get_rt_sto(entry);
	int sx;

	for (sx = 0; sx < ZPCI_TABLE_ENTRIES; sx++)
		if (reg_entry_isvalid(sto[sx]))
			dma_free_page_table(get_st_pto(sto[sx]));

	dma_free_cpu_table(sto);
}