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
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  index; } ;
typedef  int int64_t ;

/* Variables and functions */
 int default_max_percent_split_change ; 
 int git_config_get_max_percent_split_change () ; 

__attribute__((used)) static int too_many_not_shared_entries(struct index_state *istate)
{
	int i, not_shared = 0;
	int max_split = git_config_get_max_percent_split_change();

	switch (max_split) {
	case -1:
		/* not or badly configured: use the default value */
		max_split = default_max_percent_split_change;
		break;
	case 0:
		return 1; /* 0% means always write a new shared index */
	case 100:
		return 0; /* 100% means never write a new shared index */
	default:
		break; /* just use the configured value */
	}

	/* Count not shared entries */
	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];
		if (!ce->index)
			not_shared++;
	}

	return (int64_t)istate->cache_nr * max_split < (int64_t)not_shared * 100;
}