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
struct pack_list {struct pack_list* next; int /*<<< orphan*/  remaining_objects; } ;

/* Variables and functions */
 struct pack_list* altodb_packs ; 
 int /*<<< orphan*/  llist_sorted_difference_inplace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pack_list* local_packs ; 

__attribute__((used)) static void scan_alt_odb_packs(void)
{
	struct pack_list *local, *alt;

	alt = altodb_packs;
	while (alt) {
		local = local_packs;
		while (local) {
			llist_sorted_difference_inplace(local->remaining_objects,
							alt->remaining_objects);
			local = local->next;
		}
		alt = alt->next;
	}
}