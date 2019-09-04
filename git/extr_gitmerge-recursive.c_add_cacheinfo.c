#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct merge_options {TYPE_1__* repo; } ;
struct index_state {int dummy; } ;
struct cache_entry {int dummy; } ;
struct TYPE_2__ {struct index_state* index; } ;

/* Variables and functions */
 int CE_MATCH_IGNORE_MISSING ; 
 int CE_MATCH_REFRESH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int add_index_entry (struct index_state*,struct cache_entry*,int) ; 
 int err (struct merge_options*,int /*<<< orphan*/ ,char const*) ; 
 struct cache_entry* make_cache_entry (struct index_state*,unsigned int,struct object_id const*,char const*,int,int /*<<< orphan*/ ) ; 
 struct object_id const null_oid ; 
 struct cache_entry* refresh_cache_entry (struct index_state*,struct cache_entry*,int) ; 

__attribute__((used)) static int add_cacheinfo(struct merge_options *o,
			 unsigned int mode, const struct object_id *oid,
			 const char *path, int stage, int refresh, int options)
{
	struct index_state *istate = o->repo->index;
	struct cache_entry *ce;
	int ret;

	ce = make_cache_entry(istate, mode, oid ? oid : &null_oid, path, stage, 0);
	if (!ce)
		return err(o, _("add_cacheinfo failed for path '%s'; merge aborting."), path);

	ret = add_index_entry(istate, ce, options);
	if (refresh) {
		struct cache_entry *nce;

		nce = refresh_cache_entry(istate, ce,
					  CE_MATCH_REFRESH | CE_MATCH_IGNORE_MISSING);
		if (!nce)
			return err(o, _("add_cacheinfo failed to refresh for path '%s'; merge aborting."), path);
		if (nce != ce)
			ret = add_index_entry(istate, nce, options);
	}
	return ret;
}