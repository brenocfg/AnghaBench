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
struct index_state {int /*<<< orphan*/  name_hash; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 struct cache_entry* hashmap_get_from_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cache_entry* hashmap_get_next (int /*<<< orphan*/ *,struct cache_entry*) ; 
 int /*<<< orphan*/  lazy_init_name_hash (struct index_state*) ; 
 int /*<<< orphan*/  memihash (char const*,int) ; 
 scalar_t__ same_name (struct cache_entry*,char const*,int,int) ; 

struct cache_entry *index_file_exists(struct index_state *istate, const char *name, int namelen, int icase)
{
	struct cache_entry *ce;

	lazy_init_name_hash(istate);

	ce = hashmap_get_from_hash(&istate->name_hash,
				   memihash(name, namelen), NULL);
	while (ce) {
		if (same_name(ce, name, namelen, icase))
			return ce;
		ce = hashmap_get_next(&istate->name_hash, ce);
	}
	return NULL;
}