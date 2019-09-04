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
struct cache_entry {scalar_t__ mem_pool_allocated; int /*<<< orphan*/  ce_namelen; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_entry_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cache_entry*) ; 
 int /*<<< orphan*/  memset (struct cache_entry*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ should_validate_cache_entries () ; 

void discard_cache_entry(struct cache_entry *ce)
{
	if (ce && should_validate_cache_entries())
		memset(ce, 0xCD, cache_entry_size(ce->ce_namelen));

	if (ce && ce->mem_pool_allocated)
		return;

	free(ce);
}