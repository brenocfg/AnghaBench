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
struct subprocess_entry {char const* cmd; int /*<<< orphan*/  ent; } ;
struct hashmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ent ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct subprocess_entry* hashmap_get_entry (struct hashmap*,struct subprocess_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strhash (char const*) ; 

struct subprocess_entry *subprocess_find_entry(struct hashmap *hashmap, const char *cmd)
{
	struct subprocess_entry key;

	hashmap_entry_init(&key.ent, strhash(cmd));
	key.cmd = cmd;
	return hashmap_get_entry(hashmap, &key, ent, NULL);
}