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
struct cache_entry_ {int dummy; } ;
struct cache_ {size_t entries_size; struct cache_entry_** entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (int (*) (struct cache_*,char const*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct cache_*,char const*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_cache_entry (struct cache_entry_*) ; 
 struct cache_entry_** find_cache_entry_p (struct cache_*,char const*) ; 
 int /*<<< orphan*/  memmove (struct cache_entry_**,struct cache_entry_**,int) ; 

int
unregister_cache_entry(struct cache_ *the_cache, const char *entry_name)
{
	struct cache_entry_ **del_ent;

	TRACE_IN(unregister_cache_entry);
	assert(the_cache != NULL);

	del_ent = find_cache_entry_p(the_cache, entry_name);
	if (del_ent != NULL) {
		destroy_cache_entry(*del_ent);
		--the_cache->entries_size;

		memmove(del_ent, del_ent + 1,
			(&(the_cache->entries[--the_cache->entries_size]) -
	    		del_ent) * sizeof(struct cache_entry_ *));

		TRACE_OUT(unregister_cache_entry);
		return (0);
	} else {
		TRACE_OUT(unregister_cache_entry);
		return (-1);
	}
}