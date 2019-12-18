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
struct object_id {int dummy; } ;
struct cache_entry {int ce_namelen; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 unsigned short S_IFDIR ; 
 int /*<<< orphan*/  create_ce_flags (int) ; 
 int /*<<< orphan*/  create_ce_mode (unsigned short) ; 
 int /*<<< orphan*/  error (char*,char const*,char const*) ; 
 scalar_t__ get_tree_entry (int /*<<< orphan*/ ,struct object_id*,char const*,struct object_id*,unsigned short*) ; 
 struct cache_entry* make_empty_cache_entry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  the_index ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static struct cache_entry *read_one_ent(const char *which,
					struct object_id *ent, const char *path,
					int namelen, int stage)
{
	unsigned short mode;
	struct object_id oid;
	struct cache_entry *ce;

	if (get_tree_entry(the_repository, ent, path, &oid, &mode)) {
		if (which)
			error("%s: not in %s branch.", path, which);
		return NULL;
	}
	if (mode == S_IFDIR) {
		if (which)
			error("%s: not a blob in %s branch.", path, which);
		return NULL;
	}
	ce = make_empty_cache_entry(&the_index, namelen);

	oidcpy(&ce->oid, &oid);
	memcpy(ce->name, path, namelen);
	ce->ce_flags = create_ce_flags(stage);
	ce->ce_namelen = namelen;
	ce->ce_mode = create_ce_mode(mode);
	return ce;
}