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
struct path_and_oids_entry {char* path; int /*<<< orphan*/  trees; int /*<<< orphan*/  ent; } ;
struct object_id {int dummy; } ;
struct hashmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ent ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int) ; 
 struct path_and_oids_entry* hashmap_get_entry (struct hashmap*,struct path_and_oids_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_put (struct hashmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidset_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oidset_insert (int /*<<< orphan*/ *,struct object_id const*) ; 
 int strhash (char const*) ; 
 struct path_and_oids_entry* xcalloc (int,int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void paths_and_oids_insert(struct hashmap *map,
				  const char *path,
				  const struct object_id *oid)
{
	int hash = strhash(path);
	struct path_and_oids_entry key;
	struct path_and_oids_entry *entry;

	hashmap_entry_init(&key.ent, hash);

	/* use a shallow copy for the lookup */
	key.path = (char *)path;
	oidset_init(&key.trees, 0);

	entry = hashmap_get_entry(map, &key, ent, NULL);
	if (!entry) {
		entry = xcalloc(1, sizeof(struct path_and_oids_entry));
		hashmap_entry_init(&entry->ent, hash);
		entry->path = xstrdup(key.path);
		oidset_init(&entry->trees, 16);
		hashmap_put(map, &entry->ent);
	}

	oidset_insert(&entry->trees, oid);
}