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
struct pathspec_item {char* match; int len; int magic; int nowildcard_len; scalar_t__ attr_match_nr; scalar_t__ prefix; } ;
struct index_state {int dummy; } ;

/* Variables and functions */
 unsigned int DO_MATCH_DIRECTORY ; 
 unsigned int DO_MATCH_LEADING_PATHSPEC ; 
 int MATCHED_EXACTLY ; 
 int MATCHED_FNMATCH ; 
 int MATCHED_RECURSIVELY ; 
 int MATCHED_RECURSIVELY_LEADING_PATHSPEC ; 
 int PATHSPEC_ICASE ; 
 int /*<<< orphan*/  git_fnmatch (struct pathspec_item const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  match_pathspec_attrs (struct index_state const*,char const*,int,struct pathspec_item const*) ; 
 scalar_t__ ps_strncmp (struct pathspec_item const*,char const*,char const*,int) ; 
 scalar_t__ strncmp (char*,char const*,scalar_t__) ; 

__attribute__((used)) static int match_pathspec_item(const struct index_state *istate,
			       const struct pathspec_item *item, int prefix,
			       const char *name, int namelen, unsigned flags)
{
	/* name/namelen has prefix cut off by caller */
	const char *match = item->match + prefix;
	int matchlen = item->len - prefix;

	/*
	 * The normal call pattern is:
	 * 1. prefix = common_prefix_len(ps);
	 * 2. prune something, or fill_directory
	 * 3. match_pathspec()
	 *
	 * 'prefix' at #1 may be shorter than the command's prefix and
	 * it's ok for #2 to match extra files. Those extras will be
	 * trimmed at #3.
	 *
	 * Suppose the pathspec is 'foo' and '../bar' running from
	 * subdir 'xyz'. The common prefix at #1 will be empty, thanks
	 * to "../". We may have xyz/foo _and_ XYZ/foo after #2. The
	 * user does not want XYZ/foo, only the "foo" part should be
	 * case-insensitive. We need to filter out XYZ/foo here. In
	 * other words, we do not trust the caller on comparing the
	 * prefix part when :(icase) is involved. We do exact
	 * comparison ourselves.
	 *
	 * Normally the caller (common_prefix_len() in fact) does
	 * _exact_ matching on name[-prefix+1..-1] and we do not need
	 * to check that part. Be defensive and check it anyway, in
	 * case common_prefix_len is changed, or a new caller is
	 * introduced that does not use common_prefix_len.
	 *
	 * If the penalty turns out too high when prefix is really
	 * long, maybe change it to
	 * strncmp(match, name, item->prefix - prefix)
	 */
	if (item->prefix && (item->magic & PATHSPEC_ICASE) &&
	    strncmp(item->match, name - prefix, item->prefix))
		return 0;

	if (item->attr_match_nr &&
	    !match_pathspec_attrs(istate, name, namelen, item))
		return 0;

	/* If the match was just the prefix, we matched */
	if (!*match)
		return MATCHED_RECURSIVELY;

	if (matchlen <= namelen && !ps_strncmp(item, match, name, matchlen)) {
		if (matchlen == namelen)
			return MATCHED_EXACTLY;

		if (match[matchlen-1] == '/' || name[matchlen] == '/')
			return MATCHED_RECURSIVELY;
	} else if ((flags & DO_MATCH_DIRECTORY) &&
		   match[matchlen - 1] == '/' &&
		   namelen == matchlen - 1 &&
		   !ps_strncmp(item, match, name, namelen))
		return MATCHED_EXACTLY;

	if (item->nowildcard_len < item->len &&
	    !git_fnmatch(item, match, name,
			 item->nowildcard_len - prefix))
		return MATCHED_FNMATCH;

	/* Perform checks to see if "name" is a leading string of the pathspec */
	if (flags & DO_MATCH_LEADING_PATHSPEC) {
		/* name is a literal prefix of the pathspec */
		int offset = name[namelen-1] == '/' ? 1 : 0;
		if ((namelen < matchlen) &&
		    (match[namelen-offset] == '/') &&
		    !ps_strncmp(item, match, name, namelen))
			return MATCHED_RECURSIVELY_LEADING_PATHSPEC;

		/* name" doesn't match up to the first wild character */
		if (item->nowildcard_len < item->len &&
		    ps_strncmp(item, match, name,
			       item->nowildcard_len - prefix))
			return 0;

		/*
		 * Here is where we would perform a wildmatch to check if
		 * "name" can be matched as a directory (or a prefix) against
		 * the pathspec.  Since wildmatch doesn't have this capability
		 * at the present we have to punt and say that it is a match,
		 * potentially returning a false positive
		 * The submodules themselves will be able to perform more
		 * accurate matching to determine if the pathspec matches.
		 */
		return MATCHED_RECURSIVELY_LEADING_PATHSPEC;
	}

	return 0;
}