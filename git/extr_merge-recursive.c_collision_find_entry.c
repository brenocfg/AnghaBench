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
struct hashmap {int dummy; } ;
struct collision_entry {char* target_file; int /*<<< orphan*/  ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ent ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct collision_entry* hashmap_get_entry (struct hashmap*,struct collision_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strhash (char*) ; 

__attribute__((used)) static struct collision_entry *collision_find_entry(struct hashmap *hashmap,
						    char *target_file)
{
	struct collision_entry key;

	hashmap_entry_init(&key.ent, strhash(target_file));
	key.target_file = target_file;
	return hashmap_get_entry(hashmap, &key, ent, NULL);
}