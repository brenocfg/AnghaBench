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
struct strbuf {int dummy; } ;
struct pathspec_item {unsigned int magic; char* match; int len; int prefix; int nowildcard_len; int /*<<< orphan*/  flags; void* original; scalar_t__ attr_match_nr; int /*<<< orphan*/ * attr_match; int /*<<< orphan*/ * attr_check; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 unsigned int PATHSPEC_FROMTOP ; 
 unsigned int PATHSPEC_GLOB ; 
 unsigned int PATHSPEC_LITERAL ; 
 unsigned int PATHSPEC_LITERAL_PATH ; 
 int /*<<< orphan*/  PATHSPEC_ONESTAR ; 
 unsigned int PATHSPEC_PREFIX_ORIGIN ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,...) ; 
 unsigned int get_global_magic (unsigned int) ; 
 int /*<<< orphan*/  get_literal_global () ; 
 scalar_t__ no_wildcard (char*) ; 
 char* parse_element_magic (unsigned int*,int*,struct pathspec_item*,char const*) ; 
 int /*<<< orphan*/  prefix_magic (struct strbuf*,int,unsigned int) ; 
 char* prefix_path_gently (char const*,int,int*,char const*) ; 
 int simple_length (char*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 void* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static void init_pathspec_item(struct pathspec_item *item, unsigned flags,
			       const char *prefix, int prefixlen,
			       const char *elt)
{
	unsigned magic = 0, element_magic = 0;
	const char *copyfrom = elt;
	char *match;
	int pathspec_prefix = -1;

	item->attr_check = NULL;
	item->attr_match = NULL;
	item->attr_match_nr = 0;

	/* PATHSPEC_LITERAL_PATH ignores magic */
	if (flags & PATHSPEC_LITERAL_PATH) {
		magic = PATHSPEC_LITERAL;
	} else {
		copyfrom = parse_element_magic(&element_magic,
					       &pathspec_prefix,
					       item,
					       elt);
		magic |= element_magic;
		magic |= get_global_magic(element_magic);
	}

	item->magic = magic;

	if (pathspec_prefix >= 0 &&
	    (prefixlen || (prefix && *prefix)))
		BUG("'prefix' magic is supposed to be used at worktree's root");

	if ((magic & PATHSPEC_LITERAL) && (magic & PATHSPEC_GLOB))
		die(_("%s: 'literal' and 'glob' are incompatible"), elt);

	/* Create match string which will be used for pathspec matching */
	if (pathspec_prefix >= 0) {
		match = xstrdup(copyfrom);
		prefixlen = pathspec_prefix;
	} else if (magic & PATHSPEC_FROMTOP) {
		match = xstrdup(copyfrom);
		prefixlen = 0;
	} else {
		match = prefix_path_gently(prefix, prefixlen,
					   &prefixlen, copyfrom);
		if (!match)
			die(_("%s: '%s' is outside repository"), elt, copyfrom);
	}

	item->match = match;
	item->len = strlen(item->match);
	item->prefix = prefixlen;

	/*
	 * Prefix the pathspec (keep all magic) and assign to
	 * original. Useful for passing to another command.
	 */
	if ((flags & PATHSPEC_PREFIX_ORIGIN) &&
	    !get_literal_global()) {
		struct strbuf sb = STRBUF_INIT;

		/* Preserve the actual prefix length of each pattern */
		prefix_magic(&sb, prefixlen, element_magic);

		strbuf_addstr(&sb, match);
		item->original = strbuf_detach(&sb, NULL);
	} else {
		item->original = xstrdup(elt);
	}

	if (magic & PATHSPEC_LITERAL) {
		item->nowildcard_len = item->len;
	} else {
		item->nowildcard_len = simple_length(item->match);
		if (item->nowildcard_len < prefixlen)
			item->nowildcard_len = prefixlen;
	}

	item->flags = 0;
	if (magic & PATHSPEC_GLOB) {
		/*
		 * FIXME: should we enable ONESTAR in _GLOB for
		 * pattern "* * / * . c"?
		 */
	} else {
		if (item->nowildcard_len < item->len &&
		    item->match[item->nowildcard_len] == '*' &&
		    no_wildcard(item->match + item->nowildcard_len + 1))
			item->flags |= PATHSPEC_ONESTAR;
	}

	/* sanity checks, pathspec matchers assume these are sane */
	if (item->nowildcard_len > item->len ||
	    item->prefix         > item->len) {
		BUG("error initializing pathspec_item");
	}
}