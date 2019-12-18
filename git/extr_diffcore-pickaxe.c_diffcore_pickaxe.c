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
struct strbuf {char const* buf; } ;
struct diff_options {char* pickaxe; int pickaxe_opts; } ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/ * kwset_t ;

/* Variables and functions */
 int DIFF_PICKAXE_IGNORE_CASE ; 
 int DIFF_PICKAXE_KIND_G ; 
 int DIFF_PICKAXE_KIND_S ; 
 int DIFF_PICKAXE_REGEX ; 
 int REG_EXTENDED ; 
 int REG_ICASE ; 
 int REG_NEWLINE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  basic_regex_quote_buf (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  diff_grep ; 
 int /*<<< orphan*/  diff_queued_diff ; 
 int /*<<< orphan*/  has_changes ; 
 scalar_t__ has_non_ascii (char const*) ; 
 int /*<<< orphan*/ * kwsalloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kwsfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kwsincr (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kwsprep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pickaxe (int /*<<< orphan*/ *,struct diff_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcomp_or_die (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * tolower_trans_tbl ; 

void diffcore_pickaxe(struct diff_options *o)
{
	const char *needle = o->pickaxe;
	int opts = o->pickaxe_opts;
	regex_t regex, *regexp = NULL;
	kwset_t kws = NULL;

	if (opts & (DIFF_PICKAXE_REGEX | DIFF_PICKAXE_KIND_G)) {
		int cflags = REG_EXTENDED | REG_NEWLINE;
		if (o->pickaxe_opts & DIFF_PICKAXE_IGNORE_CASE)
			cflags |= REG_ICASE;
		regcomp_or_die(&regex, needle, cflags);
		regexp = &regex;
	} else if (opts & DIFF_PICKAXE_KIND_S) {
		if (o->pickaxe_opts & DIFF_PICKAXE_IGNORE_CASE &&
		    has_non_ascii(needle)) {
			struct strbuf sb = STRBUF_INIT;
			int cflags = REG_NEWLINE | REG_ICASE;

			basic_regex_quote_buf(&sb, needle);
			regcomp_or_die(&regex, sb.buf, cflags);
			strbuf_release(&sb);
			regexp = &regex;
		} else {
			kws = kwsalloc(o->pickaxe_opts & DIFF_PICKAXE_IGNORE_CASE
				       ? tolower_trans_tbl : NULL);
			kwsincr(kws, needle, strlen(needle));
			kwsprep(kws);
		}
	}

	pickaxe(&diff_queued_diff, o, regexp, kws,
		(opts & DIFF_PICKAXE_KIND_G) ? diff_grep : has_changes);

	if (regexp)
		regfree(regexp);
	if (kws)
		kwsfree(kws);
	return;
}