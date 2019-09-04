#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct unpack_trees_options {TYPE_2__* src_index; TYPE_1__* dir; } ;
struct object_id {int dummy; } ;
struct dir_struct {int /*<<< orphan*/  exclude_per_dir; } ;
typedef  struct cache_entry {char* name; int /*<<< orphan*/  oid; int /*<<< orphan*/  ce_mode; } const cache_entry ;
typedef  int /*<<< orphan*/  d ;
struct TYPE_4__ {int cache_nr; struct cache_entry const** cache; } ;
struct TYPE_3__ {int /*<<< orphan*/  exclude_per_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_REMOVE ; 
 int /*<<< orphan*/  ERROR_NOT_UPTODATE_DIR ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_entry (struct unpack_trees_options*,struct cache_entry const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int add_rejected_path (struct unpack_trees_options*,int /*<<< orphan*/ ,char*) ; 
 int ce_namelen (struct cache_entry const*) ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  invalidate_ce_path (struct cache_entry const*,struct unpack_trees_options*) ; 
 int locate_in_src_index (struct cache_entry const*,struct unpack_trees_options*) ; 
 int /*<<< orphan*/  mark_ce_used (struct cache_entry const*,struct unpack_trees_options*) ; 
 int /*<<< orphan*/  memset (struct dir_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * oid_to_hex (struct object_id*) ; 
 scalar_t__ oideq (struct object_id*,int /*<<< orphan*/ *) ; 
 int read_directory (struct dir_struct*,TYPE_2__*,char*,int,int /*<<< orphan*/ *) ; 
 int resolve_gitlink_ref (char*,char*,struct object_id*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int verify_clean_submodule (int /*<<< orphan*/ *,struct cache_entry const*,struct unpack_trees_options*) ; 
 scalar_t__ verify_uptodate (struct cache_entry const*,struct unpack_trees_options*) ; 
 char* xstrfmt (char*,int,char*) ; 

__attribute__((used)) static int verify_clean_subdirectory(const struct cache_entry *ce,
				     struct unpack_trees_options *o)
{
	/*
	 * we are about to extract "ce->name"; we would not want to lose
	 * anything in the existing directory there.
	 */
	int namelen;
	int i;
	struct dir_struct d;
	char *pathbuf;
	int cnt = 0;

	if (S_ISGITLINK(ce->ce_mode)) {
		struct object_id oid;
		int sub_head = resolve_gitlink_ref(ce->name, "HEAD", &oid);
		/*
		 * If we are not going to update the submodule, then
		 * we don't care.
		 */
		if (!sub_head && oideq(&oid, &ce->oid))
			return 0;
		return verify_clean_submodule(sub_head ? NULL : oid_to_hex(&oid),
					      ce, o);
	}

	/*
	 * First let's make sure we do not have a local modification
	 * in that directory.
	 */
	namelen = ce_namelen(ce);
	for (i = locate_in_src_index(ce, o);
	     i < o->src_index->cache_nr;
	     i++) {
		struct cache_entry *ce2 = o->src_index->cache[i];
		int len = ce_namelen(ce2);
		if (len < namelen ||
		    strncmp(ce->name, ce2->name, namelen) ||
		    ce2->name[namelen] != '/')
			break;
		/*
		 * ce2->name is an entry in the subdirectory to be
		 * removed.
		 */
		if (!ce_stage(ce2)) {
			if (verify_uptodate(ce2, o))
				return -1;
			add_entry(o, ce2, CE_REMOVE, 0);
			invalidate_ce_path(ce, o);
			mark_ce_used(ce2, o);
		}
		cnt++;
	}

	/*
	 * Then we need to make sure that we do not lose a locally
	 * present file that is not ignored.
	 */
	pathbuf = xstrfmt("%.*s/", namelen, ce->name);

	memset(&d, 0, sizeof(d));
	if (o->dir)
		d.exclude_per_dir = o->dir->exclude_per_dir;
	i = read_directory(&d, o->src_index, pathbuf, namelen+1, NULL);
	if (i)
		return add_rejected_path(o, ERROR_NOT_UPTODATE_DIR, ce->name);
	free(pathbuf);
	return cnt;
}