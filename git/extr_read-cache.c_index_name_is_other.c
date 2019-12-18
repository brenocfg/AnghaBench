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
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ce_namelen (struct cache_entry*) ; 
 int index_name_pos (struct index_state const*,char const*,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,int) ; 

int index_name_is_other(const struct index_state *istate, const char *name,
		int namelen)
{
	int pos;
	if (namelen && name[namelen - 1] == '/')
		namelen--;
	pos = index_name_pos(istate, name, namelen);
	if (0 <= pos)
		return 0;	/* exact match */
	pos = -pos - 1;
	if (pos < istate->cache_nr) {
		struct cache_entry *ce = istate->cache[pos];
		if (ce_namelen(ce) == namelen &&
		    !memcmp(ce->name, name, namelen))
			return 0; /* Yup, this one exists unmerged */
	}
	return 1;
}