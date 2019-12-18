#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct agp_bridge_data {int dummy; } ;
struct TYPE_6__ {int num_entries; } ;
struct TYPE_5__ {void* current_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  gatt; } ;

/* Variables and functions */
 TYPE_3__* A_SIZE_8 (void*) ; 
 int /*<<< orphan*/  WR_FLUSH_GATT (int) ; 
 int /*<<< orphan*/  WR_GATT (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* agp_bridge ; 
 TYPE_1__ i460 ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i460_free_gatt_table (struct agp_bridge_data *bridge)
{
	int num_entries, i;
	void *temp;

	temp = agp_bridge->current_size;

	num_entries = A_SIZE_8(temp)->num_entries;

	for (i = 0; i < num_entries; ++i)
		WR_GATT(i, 0);
	WR_FLUSH_GATT(num_entries - 1);

	iounmap(i460.gatt);
	return 0;
}