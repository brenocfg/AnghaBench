#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct pathspec {int nr; TYPE_1__* items; } ;
struct object_id {int dummy; } ;
struct lock_file {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {char* name; scalar_t__ is_submodule; } ;
struct TYPE_5__ {int nr; TYPE_3__* entry; int /*<<< orphan*/  alloc; } ;
struct TYPE_4__ {char* original; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int COMMIT_LOCK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 char MATCHED_RECURSIVELY ; 
 int /*<<< orphan*/  PATHSPEC_PREFER_CWD ; 
 int REFRESH_QUIET ; 
 int REFRESH_UNMERGED ; 
 int SKIP_IF_UNCHANGED ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct cache_entry** active_cache ; 
 int active_nr ; 
 int /*<<< orphan*/  builtin_rm_options ; 
 int /*<<< orphan*/  builtin_rm_usage ; 
 int /*<<< orphan*/  ce_path_match (int /*<<< orphan*/ *,struct cache_entry const*,struct pathspec*,char*) ; 
 scalar_t__ check_local_mod (struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  die_errno (char*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  force ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_unmatch ; 
 int /*<<< orphan*/  index_only ; 
 int /*<<< orphan*/  is_staging_gitmodules_ok (int /*<<< orphan*/ *) ; 
 TYPE_2__ list ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 int parse_options (int,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_pathspec (struct pathspec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const**) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  quiet ; 
 scalar_t__ read_cache () ; 
 int /*<<< orphan*/  recursive ; 
 int /*<<< orphan*/  refresh_index (int /*<<< orphan*/ *,int,struct pathspec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ remove_dir_recursively (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ remove_file_from_cache (char const*) ; 
 int /*<<< orphan*/  remove_path (char const*) ; 
 int /*<<< orphan*/  remove_path_from_gitmodules (char const*) ; 
 int /*<<< orphan*/  setup_work_tree () ; 
 scalar_t__ show_only ; 
 int /*<<< orphan*/  stage_updated_gitmodules (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  submodules_absorb_gitdir_if_needed () ; 
 int /*<<< orphan*/  the_index ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ *,struct lock_file*,int) ; 
 char* xcalloc (int,int) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

int cmd_rm(int argc, const char **argv, const char *prefix)
{
	struct lock_file lock_file = LOCK_INIT;
	int i;
	struct pathspec pathspec;
	char *seen;

	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, prefix, builtin_rm_options,
			     builtin_rm_usage, 0);
	if (!argc)
		usage_with_options(builtin_rm_usage, builtin_rm_options);

	if (!index_only)
		setup_work_tree();

	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);

	if (read_cache() < 0)
		die(_("index file corrupt"));

	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_CWD,
		       prefix, argv);
	refresh_index(&the_index, REFRESH_QUIET|REFRESH_UNMERGED, &pathspec, NULL, NULL);

	seen = xcalloc(pathspec.nr, 1);

	for (i = 0; i < active_nr; i++) {
		const struct cache_entry *ce = active_cache[i];
		if (!ce_path_match(&the_index, ce, &pathspec, seen))
			continue;
		ALLOC_GROW(list.entry, list.nr + 1, list.alloc);
		list.entry[list.nr].name = xstrdup(ce->name);
		list.entry[list.nr].is_submodule = S_ISGITLINK(ce->ce_mode);
		if (list.entry[list.nr++].is_submodule &&
		    !is_staging_gitmodules_ok(&the_index))
			die(_("please stage your changes to .gitmodules or stash them to proceed"));
	}

	if (pathspec.nr) {
		const char *original;
		int seen_any = 0;
		for (i = 0; i < pathspec.nr; i++) {
			original = pathspec.items[i].original;
			if (!seen[i]) {
				if (!ignore_unmatch) {
					die(_("pathspec '%s' did not match any files"),
					    original);
				}
			}
			else {
				seen_any = 1;
			}
			if (!recursive && seen[i] == MATCHED_RECURSIVELY)
				die(_("not removing '%s' recursively without -r"),
				    *original ? original : ".");
		}

		if (!seen_any)
			exit(0);
	}

	if (!index_only)
		submodules_absorb_gitdir_if_needed();

	/*
	 * If not forced, the file, the index and the HEAD (if exists)
	 * must match; but the file can already been removed, since
	 * this sequence is a natural "novice" way:
	 *
	 *	rm F; git rm F
	 *
	 * Further, if HEAD commit exists, "diff-index --cached" must
	 * report no changes unless forced.
	 */
	if (!force) {
		struct object_id oid;
		if (get_oid("HEAD", &oid))
			oidclr(&oid);
		if (check_local_mod(&oid, index_only))
			exit(1);
	}

	/*
	 * First remove the names from the index: we won't commit
	 * the index unless all of them succeed.
	 */
	for (i = 0; i < list.nr; i++) {
		const char *path = list.entry[i].name;
		if (!quiet)
			printf("rm '%s'\n", path);

		if (remove_file_from_cache(path))
			die(_("git rm: unable to remove %s"), path);
	}

	if (show_only)
		return 0;

	/*
	 * Then, unless we used "--cached", remove the filenames from
	 * the workspace. If we fail to remove the first one, we
	 * abort the "git rm" (but once we've successfully removed
	 * any file at all, we'll go ahead and commit to it all:
	 * by then we've already committed ourselves and can't fail
	 * in the middle)
	 */
	if (!index_only) {
		int removed = 0, gitmodules_modified = 0;
		struct strbuf buf = STRBUF_INIT;
		for (i = 0; i < list.nr; i++) {
			const char *path = list.entry[i].name;
			if (list.entry[i].is_submodule) {
				strbuf_reset(&buf);
				strbuf_addstr(&buf, path);
				if (remove_dir_recursively(&buf, 0))
					die(_("could not remove '%s'"), path);

				removed = 1;
				if (!remove_path_from_gitmodules(path))
					gitmodules_modified = 1;
				continue;
			}
			if (!remove_path(path)) {
				removed = 1;
				continue;
			}
			if (!removed)
				die_errno("git rm: '%s'", path);
		}
		strbuf_release(&buf);
		if (gitmodules_modified)
			stage_updated_gitmodules(&the_index);
	}

	if (write_locked_index(&the_index, &lock_file,
			       COMMIT_LOCK | SKIP_IF_UNCHANGED))
		die(_("Unable to write new index file"));

	return 0;
}