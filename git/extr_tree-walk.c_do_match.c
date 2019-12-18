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
struct strbuf {int len; char const* buf; } ;
struct pathspec_item {char* match; int len; int magic; int nowildcard_len; scalar_t__ attr_match_nr; } ;
struct pathspec {int nr; int magic; int max_depth; scalar_t__ recursive; scalar_t__ recurse_submodules; struct pathspec_item* items; scalar_t__ has_wildcard; } ;
struct name_entry {char* path; int /*<<< orphan*/  mode; } ;
struct index_state {int dummy; } ;
typedef  enum interesting { ____Placeholder_interesting } interesting ;

/* Variables and functions */
 int /*<<< orphan*/  GUARD_PATHSPEC (struct pathspec const*,int) ; 
 int PATHSPEC_ATTR ; 
 int PATHSPEC_EXCLUDE ; 
 int PATHSPEC_FROMTOP ; 
 int PATHSPEC_GLOB ; 
 int PATHSPEC_ICASE ; 
 int PATHSPEC_LITERAL ; 
 int PATHSPEC_MAXDEPTH ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int all_entries_interesting ; 
 int all_entries_not_interesting ; 
 int /*<<< orphan*/  basecmp (struct pathspec_item const*,char const*,char const*,int) ; 
 int entry_interesting ; 
 int entry_not_interesting ; 
 int /*<<< orphan*/  git_fnmatch (struct pathspec_item const*,char const*,char*,int) ; 
 int /*<<< orphan*/  match_dir_prefix (struct pathspec_item const*,char const*,char const*,int) ; 
 scalar_t__ match_entry (struct pathspec_item const*,struct name_entry const*,int,char const*,int,int*) ; 
 int match_pathspec_attrs (struct index_state*,char*,int,struct pathspec_item const*) ; 
 int /*<<< orphan*/  match_wildcard_base (struct pathspec_item const*,char const*,int,int*) ; 
 int /*<<< orphan*/  ps_strncmp (struct pathspec_item const*,char const*,char*,int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int tree_entry_len (struct name_entry const*) ; 
 scalar_t__ within_depth (char const*,int,int,int) ; 

__attribute__((used)) static enum interesting do_match(struct index_state *istate,
				 const struct name_entry *entry,
				 struct strbuf *base, int base_offset,
				 const struct pathspec *ps,
				 int exclude)
{
	int i;
	int pathlen, baselen = base->len - base_offset;
	enum interesting never_interesting = ps->has_wildcard ?
		entry_not_interesting : all_entries_not_interesting;

	GUARD_PATHSPEC(ps,
		       PATHSPEC_FROMTOP |
		       PATHSPEC_MAXDEPTH |
		       PATHSPEC_LITERAL |
		       PATHSPEC_GLOB |
		       PATHSPEC_ICASE |
		       PATHSPEC_EXCLUDE |
		       PATHSPEC_ATTR);

	if (!ps->nr) {
		if (!ps->recursive ||
		    !(ps->magic & PATHSPEC_MAXDEPTH) ||
		    ps->max_depth == -1)
			return all_entries_interesting;
		return within_depth(base->buf + base_offset, baselen,
				    !!S_ISDIR(entry->mode),
				    ps->max_depth) ?
			entry_interesting : entry_not_interesting;
	}

	pathlen = tree_entry_len(entry);

	for (i = ps->nr - 1; i >= 0; i--) {
		const struct pathspec_item *item = ps->items+i;
		const char *match = item->match;
		const char *base_str = base->buf + base_offset;
		int matchlen = item->len, matched = 0;

		if ((!exclude &&   item->magic & PATHSPEC_EXCLUDE) ||
		    ( exclude && !(item->magic & PATHSPEC_EXCLUDE)))
			continue;

		if (baselen >= matchlen) {
			/* If it doesn't match, move along... */
			if (!match_dir_prefix(item, base_str, match, matchlen))
				goto match_wildcards;

			if (!ps->recursive ||
			    !(ps->magic & PATHSPEC_MAXDEPTH) ||
			    ps->max_depth == -1) {
				if (!item->attr_match_nr)
					return all_entries_interesting;
				else
					goto interesting;
			}

			if (within_depth(base_str + matchlen + 1,
					 baselen - matchlen - 1,
					 !!S_ISDIR(entry->mode),
					 ps->max_depth))
				goto interesting;
			else
				return entry_not_interesting;
		}

		/* Either there must be no base, or the base must match. */
		if (baselen == 0 || !basecmp(item, base_str, match, baselen)) {
			if (match_entry(item, entry, pathlen,
					match + baselen, matchlen - baselen,
					&never_interesting))
				goto interesting;

			if (item->nowildcard_len < item->len) {
				if (!git_fnmatch(item, match + baselen, entry->path,
						 item->nowildcard_len - baselen))
					goto interesting;

				/*
				 * Match all directories. We'll try to
				 * match files later on.
				 */
				if (ps->recursive && S_ISDIR(entry->mode))
					return entry_interesting;

				/*
				 * When matching against submodules with
				 * wildcard characters, ensure that the entry
				 * at least matches up to the first wild
				 * character.  More accurate matching can then
				 * be performed in the submodule itself.
				 */
				if (ps->recurse_submodules &&
				    S_ISGITLINK(entry->mode) &&
				    !ps_strncmp(item, match + baselen,
						entry->path,
						item->nowildcard_len - baselen))
					goto interesting;
			}

			continue;
		}

match_wildcards:
		if (item->nowildcard_len == item->len)
			continue;

		if (item->nowildcard_len &&
		    !match_wildcard_base(item, base_str, baselen, &matched))
			continue;

		/*
		 * Concatenate base and entry->path into one and do
		 * fnmatch() on it.
		 *
		 * While we could avoid concatenation in certain cases
		 * [1], which saves a memcpy and potentially a
		 * realloc, it turns out not worth it. Measurement on
		 * linux-2.6 does not show any clear improvements,
		 * partly because of the nowildcard_len optimization
		 * in git_fnmatch(). Avoid micro-optimizations here.
		 *
		 * [1] if match_wildcard_base() says the base
		 * directory is already matched, we only need to match
		 * the rest, which is shorter so _in theory_ faster.
		 */

		strbuf_add(base, entry->path, pathlen);

		if (!git_fnmatch(item, match, base->buf + base_offset,
				 item->nowildcard_len)) {
			strbuf_setlen(base, base_offset + baselen);
			goto interesting;
		}

		/*
		 * When matching against submodules with
		 * wildcard characters, ensure that the entry
		 * at least matches up to the first wild
		 * character.  More accurate matching can then
		 * be performed in the submodule itself.
		 */
		if (ps->recurse_submodules && S_ISGITLINK(entry->mode) &&
		    !ps_strncmp(item, match, base->buf + base_offset,
				item->nowildcard_len)) {
			strbuf_setlen(base, base_offset + baselen);
			goto interesting;
		}

		strbuf_setlen(base, base_offset + baselen);

		/*
		 * Match all directories. We'll try to match files
		 * later on.
		 * max_depth is ignored but we may consider support it
		 * in future, see
		 * https://public-inbox.org/git/7vmxo5l2g4.fsf@alter.siamese.dyndns.org/
		 */
		if (ps->recursive && S_ISDIR(entry->mode))
			return entry_interesting;
		continue;
interesting:
		if (item->attr_match_nr) {
			int ret;

			/*
			 * Must not return all_entries_not_interesting
			 * prematurely. We do not know if all entries do not
			 * match some attributes with current attr API.
			 */
			never_interesting = entry_not_interesting;

			/*
			 * Consider all directories interesting (because some
			 * of those files inside may match some attributes
			 * even though the parent dir does not)
			 *
			 * FIXME: attributes _can_ match directories and we
			 * can probably return all_entries_interesting or
			 * all_entries_not_interesting here if matched.
			 */
			if (S_ISDIR(entry->mode))
				return entry_interesting;

			strbuf_add(base, entry->path, pathlen);
			ret = match_pathspec_attrs(istate, base->buf + base_offset,
						   base->len - base_offset, item);
			strbuf_setlen(base, base_offset + baselen);
			if (!ret)
				continue;
		}
		return entry_interesting;
	}
	return never_interesting; /* No matches */
}