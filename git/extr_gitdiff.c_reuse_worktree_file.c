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
struct stat {int dummy; } ;
struct object_id {int dummy; } ;
struct index_state {struct cache_entry** cache; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int CE_VALID ; 
 int /*<<< orphan*/  FAST_WORKING_DIRECTORY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ ce_skip_worktree (struct cache_entry const*) ; 
 scalar_t__ ce_uptodate (struct cache_entry const*) ; 
 scalar_t__ has_object_pack (struct object_id const*) ; 
 int /*<<< orphan*/  ie_match_stat (struct index_state*,struct cache_entry const*,struct stat*,int /*<<< orphan*/ ) ; 
 int index_name_pos (struct index_state*,char const*,int) ; 
 int /*<<< orphan*/  lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  oideq (struct object_id const*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ would_convert_to_git (struct index_state*,char const*) ; 

__attribute__((used)) static int reuse_worktree_file(struct index_state *istate,
			       const char *name,
			       const struct object_id *oid,
			       int want_file)
{
	const struct cache_entry *ce;
	struct stat st;
	int pos, len;

	/*
	 * We do not read the cache ourselves here, because the
	 * benchmark with my previous version that always reads cache
	 * shows that it makes things worse for diff-tree comparing
	 * two linux-2.6 kernel trees in an already checked out work
	 * tree.  This is because most diff-tree comparisons deal with
	 * only a small number of files, while reading the cache is
	 * expensive for a large project, and its cost outweighs the
	 * savings we get by not inflating the object to a temporary
	 * file.  Practically, this code only helps when we are used
	 * by diff-cache --cached, which does read the cache before
	 * calling us.
	 */
	if (!istate->cache)
		return 0;

	/* We want to avoid the working directory if our caller
	 * doesn't need the data in a normal file, this system
	 * is rather slow with its stat/open/mmap/close syscalls,
	 * and the object is contained in a pack file.  The pack
	 * is probably already open and will be faster to obtain
	 * the data through than the working directory.  Loose
	 * objects however would tend to be slower as they need
	 * to be individually opened and inflated.
	 */
	if (!FAST_WORKING_DIRECTORY && !want_file && has_object_pack(oid))
		return 0;

	/*
	 * Similarly, if we'd have to convert the file contents anyway, that
	 * makes the optimization not worthwhile.
	 */
	if (!want_file && would_convert_to_git(istate, name))
		return 0;

	len = strlen(name);
	pos = index_name_pos(istate, name, len);
	if (pos < 0)
		return 0;
	ce = istate->cache[pos];

	/*
	 * This is not the sha1 we are looking for, or
	 * unreusable because it is not a regular file.
	 */
	if (!oideq(oid, &ce->oid) || !S_ISREG(ce->ce_mode))
		return 0;

	/*
	 * If ce is marked as "assume unchanged", there is no
	 * guarantee that work tree matches what we are looking for.
	 */
	if ((ce->ce_flags & CE_VALID) || ce_skip_worktree(ce))
		return 0;

	/*
	 * If ce matches the file in the work tree, we can reuse it.
	 */
	if (ce_uptodate(ce) ||
	    (!lstat(name, &st) && !ie_match_stat(istate, ce, &st, 0)))
		return 1;

	return 0;
}