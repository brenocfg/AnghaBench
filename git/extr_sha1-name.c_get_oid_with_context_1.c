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
struct repository {TYPE_1__* index; int /*<<< orphan*/  refs; } ;
struct object_id {int dummy; } ;
struct object_context {void* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  symlink_path; } ;
struct handle_one_ref_cb {struct commit_list** list; struct repository* repo; } ;
struct commit_list {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
typedef  enum get_oid_result { ____Placeholder_get_oid_result } get_oid_result ;
struct TYPE_2__ {int cache_nr; struct cache_entry** cache; } ;

/* Variables and functions */
 unsigned int GET_OID_DISAMBIGUATORS ; 
 unsigned int GET_OID_FOLLOW_SYMLINKS ; 
 unsigned int GET_OID_ONLY_TO_DIE ; 
 unsigned int GET_OID_QUIETLY ; 
 unsigned int GET_OID_RECORD_PATH ; 
 unsigned int GET_OID_TREEISH ; 
 int /*<<< orphan*/  S_IFINVALID ; 
 int ce_namelen (struct cache_entry const*) ; 
 int ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  commit_list_sort_by_date (struct commit_list**) ; 
 int /*<<< orphan*/  diagnose_invalid_index_path (struct repository*,int,char const*,char const*) ; 
 int /*<<< orphan*/  diagnose_invalid_oid_path (struct repository*,char const*,char const*,struct object_id*,char const*,int) ; 
 int /*<<< orphan*/  die (char*,int,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_oid_1 (struct repository*,char const*,int,struct object_id*,unsigned int) ; 
 int get_oid_oneline (struct repository*,char const*,struct object_id*,struct commit_list*) ; 
 int get_tree_entry (struct repository*,struct object_id*,char const*,struct object_id*,int /*<<< orphan*/ *) ; 
 int get_tree_entry_follow_symlinks (struct repository*,struct object_id*,char const*,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_one_ref ; 
 int index_name_pos (TYPE_1__*,char const*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (struct object_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refs_for_each_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct handle_one_ref_cb*) ; 
 int /*<<< orphan*/  refs_head_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct handle_one_ref_cb*) ; 
 int /*<<< orphan*/  repo_read_index (struct repository*) ; 
 char* resolve_relative_path (struct repository*,char const*) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static enum get_oid_result get_oid_with_context_1(struct repository *repo,
				  const char *name,
				  unsigned flags,
				  const char *prefix,
				  struct object_id *oid,
				  struct object_context *oc)
{
	int ret, bracket_depth;
	int namelen = strlen(name);
	const char *cp;
	int only_to_die = flags & GET_OID_ONLY_TO_DIE;

	if (only_to_die)
		flags |= GET_OID_QUIETLY;

	memset(oc, 0, sizeof(*oc));
	oc->mode = S_IFINVALID;
	strbuf_init(&oc->symlink_path, 0);
	ret = get_oid_1(repo, name, namelen, oid, flags);
	if (!ret)
		return ret;
	/*
	 * sha1:path --> object name of path in ent sha1
	 * :path -> object name of absolute path in index
	 * :./path -> object name of path relative to cwd in index
	 * :[0-3]:path -> object name of path in index at stage
	 * :/foo -> recent commit matching foo
	 */
	if (name[0] == ':') {
		int stage = 0;
		const struct cache_entry *ce;
		char *new_path = NULL;
		int pos;
		if (!only_to_die && namelen > 2 && name[1] == '/') {
			struct handle_one_ref_cb cb;
			struct commit_list *list = NULL;

			cb.repo = repo;
			cb.list = &list;
			refs_for_each_ref(repo->refs, handle_one_ref, &cb);
			refs_head_ref(repo->refs, handle_one_ref, &cb);
			commit_list_sort_by_date(&list);
			return get_oid_oneline(repo, name + 2, oid, list);
		}
		if (namelen < 3 ||
		    name[2] != ':' ||
		    name[1] < '0' || '3' < name[1])
			cp = name + 1;
		else {
			stage = name[1] - '0';
			cp = name + 3;
		}
		new_path = resolve_relative_path(repo, cp);
		if (!new_path) {
			namelen = namelen - (cp - name);
		} else {
			cp = new_path;
			namelen = strlen(cp);
		}

		if (flags & GET_OID_RECORD_PATH)
			oc->path = xstrdup(cp);

		if (!repo->index || !repo->index->cache)
			repo_read_index(repo);
		pos = index_name_pos(repo->index, cp, namelen);
		if (pos < 0)
			pos = -pos - 1;
		while (pos < repo->index->cache_nr) {
			ce = repo->index->cache[pos];
			if (ce_namelen(ce) != namelen ||
			    memcmp(ce->name, cp, namelen))
				break;
			if (ce_stage(ce) == stage) {
				oidcpy(oid, &ce->oid);
				oc->mode = ce->ce_mode;
				free(new_path);
				return 0;
			}
			pos++;
		}
		if (only_to_die && name[1] && name[1] != '/')
			diagnose_invalid_index_path(repo, stage, prefix, cp);
		free(new_path);
		return -1;
	}
	for (cp = name, bracket_depth = 0; *cp; cp++) {
		if (*cp == '{')
			bracket_depth++;
		else if (bracket_depth && *cp == '}')
			bracket_depth--;
		else if (!bracket_depth && *cp == ':')
			break;
	}
	if (*cp == ':') {
		struct object_id tree_oid;
		int len = cp - name;
		unsigned sub_flags = flags;

		sub_flags &= ~GET_OID_DISAMBIGUATORS;
		sub_flags |= GET_OID_TREEISH;

		if (!get_oid_1(repo, name, len, &tree_oid, sub_flags)) {
			const char *filename = cp+1;
			char *new_filename = NULL;

			new_filename = resolve_relative_path(repo, filename);
			if (new_filename)
				filename = new_filename;
			if (flags & GET_OID_FOLLOW_SYMLINKS) {
				ret = get_tree_entry_follow_symlinks(repo, &tree_oid,
					filename, oid, &oc->symlink_path,
					&oc->mode);
			} else {
				ret = get_tree_entry(repo, &tree_oid, filename, oid,
						     &oc->mode);
				if (ret && only_to_die) {
					diagnose_invalid_oid_path(repo, prefix,
								   filename,
								   &tree_oid,
								   name, len);
				}
			}
			if (flags & GET_OID_RECORD_PATH)
				oc->path = xstrdup(filename);

			free(new_filename);
			return ret;
		} else {
			if (only_to_die)
				die("Invalid object name '%.*s'.", len, name);
		}
	}
	return ret;
}