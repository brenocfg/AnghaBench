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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct object_id {int dummy; } ;
struct index_state {struct cache_entry** cache; } ;
struct cache_entry {int ce_namelen; scalar_t__ ce_mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int ADD_CACHE_INTENT ; 
 int ADD_CACHE_NEW_ONLY ; 
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_OK_TO_REPLACE ; 
 int ADD_CACHE_PRETEND ; 
 int ADD_CACHE_RENORMALIZE ; 
 int ADD_CACHE_VERBOSE ; 
 int /*<<< orphan*/  CE_ADDED ; 
 int /*<<< orphan*/  CE_INTENT_TO_ADD ; 
 unsigned int CE_MATCH_IGNORE_SKIP_WORKTREE ; 
 unsigned int CE_MATCH_IGNORE_VALID ; 
 unsigned int CE_MATCH_RACY_IS_DIRTY ; 
 int HASH_RENORMALIZE ; 
 int HASH_WRITE_OBJECT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISGITLINK (scalar_t__) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ add_index_entry (struct index_state*,struct cache_entry*,int) ; 
 int /*<<< orphan*/  adjust_dirname_case (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_mark_uptodate (struct cache_entry*) ; 
 scalar_t__ ce_mode_from_stat (struct cache_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry*) ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry*) ; 
 struct cache_entry* create_alias_ce (struct index_state*,struct cache_entry*,struct cache_entry*) ; 
 scalar_t__ create_ce_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ different_name (struct cache_entry*,struct cache_entry*) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fill_stat_cache_info (struct index_state*,struct cache_entry*,struct stat*) ; 
 scalar_t__ has_symlinks ; 
 int /*<<< orphan*/  ie_match_stat (struct index_state*,struct cache_entry*,struct stat*,unsigned int) ; 
 scalar_t__ ignore_case ; 
 struct cache_entry* index_file_exists (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int index_name_pos_also_unmerged (struct index_state*,char const*,int) ; 
 scalar_t__ index_path (struct index_state*,int /*<<< orphan*/ *,char const*,struct stat*,int) ; 
 struct cache_entry* make_empty_cache_entry (struct index_state*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ resolve_gitlink_ref (char const*,char*,struct object_id*) ; 
 int /*<<< orphan*/  set_object_name_for_intent_to_add_entry (struct cache_entry*) ; 
 int strlen (char const*) ; 
 scalar_t__ trust_executable_bit ; 

int add_to_index(struct index_state *istate, const char *path, struct stat *st, int flags)
{
	int namelen, was_same;
	mode_t st_mode = st->st_mode;
	struct cache_entry *ce, *alias = NULL;
	unsigned ce_option = CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE|CE_MATCH_RACY_IS_DIRTY;
	int verbose = flags & (ADD_CACHE_VERBOSE | ADD_CACHE_PRETEND);
	int pretend = flags & ADD_CACHE_PRETEND;
	int intent_only = flags & ADD_CACHE_INTENT;
	int add_option = (ADD_CACHE_OK_TO_ADD|ADD_CACHE_OK_TO_REPLACE|
			  (intent_only ? ADD_CACHE_NEW_ONLY : 0));
	int hash_flags = HASH_WRITE_OBJECT;
	struct object_id oid;

	if (flags & ADD_CACHE_RENORMALIZE)
		hash_flags |= HASH_RENORMALIZE;

	if (!S_ISREG(st_mode) && !S_ISLNK(st_mode) && !S_ISDIR(st_mode))
		return error(_("%s: can only add regular files, symbolic links or git-directories"), path);

	namelen = strlen(path);
	if (S_ISDIR(st_mode)) {
		if (resolve_gitlink_ref(path, "HEAD", &oid) < 0)
			return error(_("'%s' does not have a commit checked out"), path);
		while (namelen && path[namelen-1] == '/')
			namelen--;
	}
	ce = make_empty_cache_entry(istate, namelen);
	memcpy(ce->name, path, namelen);
	ce->ce_namelen = namelen;
	if (!intent_only)
		fill_stat_cache_info(istate, ce, st);
	else
		ce->ce_flags |= CE_INTENT_TO_ADD;


	if (trust_executable_bit && has_symlinks) {
		ce->ce_mode = create_ce_mode(st_mode);
	} else {
		/* If there is an existing entry, pick the mode bits and type
		 * from it, otherwise assume unexecutable regular file.
		 */
		struct cache_entry *ent;
		int pos = index_name_pos_also_unmerged(istate, path, namelen);

		ent = (0 <= pos) ? istate->cache[pos] : NULL;
		ce->ce_mode = ce_mode_from_stat(ent, st_mode);
	}

	/* When core.ignorecase=true, determine if a directory of the same name but differing
	 * case already exists within the Git repository.  If it does, ensure the directory
	 * case of the file being added to the repository matches (is folded into) the existing
	 * entry's directory case.
	 */
	if (ignore_case) {
		adjust_dirname_case(istate, ce->name);
	}
	if (!(flags & ADD_CACHE_RENORMALIZE)) {
		alias = index_file_exists(istate, ce->name,
					  ce_namelen(ce), ignore_case);
		if (alias &&
		    !ce_stage(alias) &&
		    !ie_match_stat(istate, alias, st, ce_option)) {
			/* Nothing changed, really */
			if (!S_ISGITLINK(alias->ce_mode))
				ce_mark_uptodate(alias);
			alias->ce_flags |= CE_ADDED;

			discard_cache_entry(ce);
			return 0;
		}
	}
	if (!intent_only) {
		if (index_path(istate, &ce->oid, path, st, hash_flags)) {
			discard_cache_entry(ce);
			return error(_("unable to index file '%s'"), path);
		}
	} else
		set_object_name_for_intent_to_add_entry(ce);

	if (ignore_case && alias && different_name(ce, alias))
		ce = create_alias_ce(istate, ce, alias);
	ce->ce_flags |= CE_ADDED;

	/* It was suspected to be racily clean, but it turns out to be Ok */
	was_same = (alias &&
		    !ce_stage(alias) &&
		    oideq(&alias->oid, &ce->oid) &&
		    ce->ce_mode == alias->ce_mode);

	if (pretend)
		discard_cache_entry(ce);
	else if (add_index_entry(istate, ce, add_option)) {
		discard_cache_entry(ce);
		return error(_("unable to add '%s' to index"), path);
	}
	if (verbose && !was_same)
		printf("add '%s'\n", path);
	return 0;
}