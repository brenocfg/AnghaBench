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
struct strbuf {int dummy; } ;
struct rev_info {int /*<<< orphan*/  repo; } ;
struct index_state {int cache_nr; scalar_t__ cache_tree; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {unsigned int flags; } ;
struct blob {TYPE_1__ object; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_cache_tree (scalar_t__,struct rev_info*,struct strbuf*,unsigned int) ; 
 int /*<<< orphan*/  add_pending_object_with_path (struct rev_info*,TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 struct blob* lookup_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void do_add_index_objects_to_pending(struct rev_info *revs,
					    struct index_state *istate,
					    unsigned int flags)
{
	int i;

	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];
		struct blob *blob;

		if (S_ISGITLINK(ce->ce_mode))
			continue;

		blob = lookup_blob(revs->repo, &ce->oid);
		if (!blob)
			die("unable to add index blob to traversal");
		blob->object.flags |= flags;
		add_pending_object_with_path(revs, &blob->object, "",
					     ce->ce_mode, ce->name);
	}

	if (istate->cache_tree) {
		struct strbuf path = STRBUF_INIT;
		add_cache_tree(istate->cache_tree, revs, &path, flags);
		strbuf_release(&path);
	}
}