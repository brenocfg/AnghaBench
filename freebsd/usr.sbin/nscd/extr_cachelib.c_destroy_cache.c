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
struct cache_ {size_t entries_size; struct cache_* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct cache_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct cache_*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_cache_entry (struct cache_) ; 
 int /*<<< orphan*/  free (struct cache_*) ; 

void
destroy_cache(struct cache_ *the_cache)
{

	TRACE_IN(destroy_cache);
	assert(the_cache != NULL);

	if (the_cache->entries != NULL) {
		size_t i;
		for (i = 0; i < the_cache->entries_size; ++i)
			destroy_cache_entry(the_cache->entries[i]);

		free(the_cache->entries);
	}

	free(the_cache);
	TRACE_OUT(destroy_cache);
}