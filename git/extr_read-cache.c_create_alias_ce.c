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
struct index_state {int dummy; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CE_ADDED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int ce_namelen (struct cache_entry*) ; 
 int /*<<< orphan*/  copy_cache_entry (struct cache_entry*,struct cache_entry*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cache_entry* make_empty_cache_entry (struct index_state*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_or_free_index_entry (struct index_state*,struct cache_entry*) ; 

__attribute__((used)) static struct cache_entry *create_alias_ce(struct index_state *istate,
					   struct cache_entry *ce,
					   struct cache_entry *alias)
{
	int len;
	struct cache_entry *new_entry;

	if (alias->ce_flags & CE_ADDED)
		die(_("will not add file alias '%s' ('%s' already exists in index)"),
		    ce->name, alias->name);

	/* Ok, create the new entry using the name of the existing alias */
	len = ce_namelen(alias);
	new_entry = make_empty_cache_entry(istate, len);
	memcpy(new_entry->name, alias->name, len);
	copy_cache_entry(new_entry, ce);
	save_or_free_index_entry(istate, ce);
	return new_entry;
}