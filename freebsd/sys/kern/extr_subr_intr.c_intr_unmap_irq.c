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
typedef  size_t u_int ;
struct intr_map_entry {int /*<<< orphan*/  map_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_INTRNG ; 
 int /*<<< orphan*/  free (struct intr_map_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_free_intr_map_data (int /*<<< orphan*/ ) ; 
 struct intr_map_entry** irq_map ; 
 size_t irq_map_count ; 
 size_t irq_map_first_free_idx ; 
 int /*<<< orphan*/  irq_map_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,size_t) ; 

void
intr_unmap_irq(u_int res_id)
{
	struct intr_map_entry *entry;

	mtx_lock(&irq_map_lock);
	if ((res_id >= irq_map_count) || (irq_map[res_id] == NULL))
		panic("Attempt to unmap invalid resource id: %u\n", res_id);
	entry = irq_map[res_id];
	irq_map[res_id] = NULL;
	irq_map_first_free_idx = res_id;
	mtx_unlock(&irq_map_lock);
	intr_free_intr_map_data(entry->map_data);
	free(entry, M_INTRNG);
}