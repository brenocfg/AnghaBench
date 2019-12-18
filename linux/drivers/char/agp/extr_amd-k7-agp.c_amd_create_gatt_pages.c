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
struct amd_page_map {int dummy; } ;
struct TYPE_2__ {int num_tables; struct amd_page_map** gatt_pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int amd_create_page_map (struct amd_page_map*) ; 
 int /*<<< orphan*/  amd_free_gatt_pages () ; 
 TYPE_1__ amd_irongate_private ; 
 struct amd_page_map** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct amd_page_map* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd_create_gatt_pages(int nr_tables)
{
	struct amd_page_map **tables;
	struct amd_page_map *entry;
	int retval = 0;
	int i;

	tables = kcalloc(nr_tables + 1, sizeof(struct amd_page_map *),
			 GFP_KERNEL);
	if (tables == NULL)
		return -ENOMEM;

	for (i = 0; i < nr_tables; i++) {
		entry = kzalloc(sizeof(struct amd_page_map), GFP_KERNEL);
		tables[i] = entry;
		if (entry == NULL) {
			retval = -ENOMEM;
			break;
		}
		retval = amd_create_page_map(entry);
		if (retval != 0)
			break;
	}
	amd_irongate_private.num_tables = i;
	amd_irongate_private.gatt_pages = tables;

	if (retval != 0)
		amd_free_gatt_pages();

	return retval;
}