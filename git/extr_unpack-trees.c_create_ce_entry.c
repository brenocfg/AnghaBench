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
struct traverse_info {int dummy; } ;
struct name_entry {int /*<<< orphan*/  pathlen; int /*<<< orphan*/  path; int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;
struct index_state {int dummy; } ;
struct cache_entry {size_t ce_namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  oid; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_ce_flags (int) ; 
 int /*<<< orphan*/  create_ce_mode (int /*<<< orphan*/ ) ; 
 struct cache_entry* make_empty_cache_entry (struct index_state*,size_t) ; 
 struct cache_entry* make_empty_transient_cache_entry (size_t) ; 
 int /*<<< orphan*/  make_traverse_path (int /*<<< orphan*/ ,size_t,struct traverse_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t traverse_path_len (struct traverse_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_entry_len (struct name_entry const*) ; 

__attribute__((used)) static struct cache_entry *create_ce_entry(const struct traverse_info *info,
	const struct name_entry *n,
	int stage,
	struct index_state *istate,
	int is_transient)
{
	size_t len = traverse_path_len(info, tree_entry_len(n));
	struct cache_entry *ce =
		is_transient ?
		make_empty_transient_cache_entry(len) :
		make_empty_cache_entry(istate, len);

	ce->ce_mode = create_ce_mode(n->mode);
	ce->ce_flags = create_ce_flags(stage);
	ce->ce_namelen = len;
	oidcpy(&ce->oid, &n->oid);
	/* len+1 because the cache_entry allocates space for NUL */
	make_traverse_path(ce->name, len + 1, info, n->path, n->pathlen);

	return ce;
}