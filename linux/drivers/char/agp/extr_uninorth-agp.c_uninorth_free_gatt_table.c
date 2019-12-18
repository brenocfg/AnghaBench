#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct agp_bridge_data {scalar_t__ gatt_table_real; int /*<<< orphan*/  gatt_table; void* current_size; } ;
struct TYPE_4__ {int page_order; } ;
struct TYPE_3__ {int /*<<< orphan*/  pages_arr; } ;

/* Variables and functions */
 TYPE_2__* A_SIZE_32 (void*) ; 
 int /*<<< orphan*/  ClearPageReserved (struct page*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 TYPE_1__ uninorth_priv ; 
 struct page* virt_to_page (char*) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uninorth_free_gatt_table(struct agp_bridge_data *bridge)
{
	int page_order;
	char *table, *table_end;
	void *temp;
	struct page *page;

	temp = bridge->current_size;
	page_order = A_SIZE_32(temp)->page_order;

	/* Do not worry about freeing memory, because if this is
	 * called, then all agp memory is deallocated and removed
	 * from the table.
	 */

	vunmap(bridge->gatt_table);
	kfree(uninorth_priv.pages_arr);
	table = (char *) bridge->gatt_table_real;
	table_end = table + ((PAGE_SIZE * (1 << page_order)) - 1);

	for (page = virt_to_page(table); page <= virt_to_page(table_end); page++)
		ClearPageReserved(page);

	free_pages((unsigned long) bridge->gatt_table_real, page_order);

	return 0;
}