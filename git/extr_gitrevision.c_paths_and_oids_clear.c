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
struct path_and_oids_entry {int /*<<< orphan*/  path; int /*<<< orphan*/  trees; } ;
struct hashmap_iter {int dummy; } ;
struct hashmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (struct hashmap*,int) ; 
 int /*<<< orphan*/  hashmap_iter_init (struct hashmap*,struct hashmap_iter*) ; 
 scalar_t__ hashmap_iter_next (struct hashmap_iter*) ; 
 int /*<<< orphan*/  oidset_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void paths_and_oids_clear(struct hashmap *map)
{
	struct hashmap_iter iter;
	struct path_and_oids_entry *entry;
	hashmap_iter_init(map, &iter);

	while ((entry = (struct path_and_oids_entry *)hashmap_iter_next(&iter))) {
		oidset_clear(&entry->trees);
		free(entry->path);
	}

	hashmap_free(map, 1);
}