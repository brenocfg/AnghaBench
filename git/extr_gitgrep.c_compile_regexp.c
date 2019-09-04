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
struct grep_pat {int fixed; int /*<<< orphan*/  regexp; int /*<<< orphan*/  pattern; scalar_t__ ignore_case; int /*<<< orphan*/  kws; int /*<<< orphan*/  patternlen; int /*<<< orphan*/  word_regexp; } ;
struct grep_opt {scalar_t__ extended_regexp_option; scalar_t__ pcre1; scalar_t__ pcre2; scalar_t__ fixed; scalar_t__ ignore_case; int /*<<< orphan*/  word_regexp; } ;

/* Variables and functions */
 int REG_EXTENDED ; 
 int REG_ICASE ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  compile_fixed_regexp (struct grep_pat*,struct grep_opt*) ; 
 int /*<<< orphan*/  compile_pcre1_regexp (struct grep_pat*,struct grep_opt*) ; 
 int /*<<< orphan*/  compile_pcre2_pattern (struct grep_pat*,struct grep_opt*) ; 
 int /*<<< orphan*/  compile_regexp_failed (struct grep_pat*,char*) ; 
 int /*<<< orphan*/  has_non_ascii (int /*<<< orphan*/ ) ; 
 scalar_t__ has_null (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_fixed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kwsalloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kwsincr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kwsprep (int /*<<< orphan*/ ) ; 
 int regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * tolower_trans_tbl ; 

__attribute__((used)) static void compile_regexp(struct grep_pat *p, struct grep_opt *opt)
{
	int ascii_only;
	int err;
	int regflags = REG_NEWLINE;

	p->word_regexp = opt->word_regexp;
	p->ignore_case = opt->ignore_case;
	ascii_only     = !has_non_ascii(p->pattern);

	/*
	 * Even when -F (fixed) asks us to do a non-regexp search, we
	 * may not be able to correctly case-fold when -i
	 * (ignore-case) is asked (in which case, we'll synthesize a
	 * regexp to match the pattern that matches regexp special
	 * characters literally, while ignoring case differences).  On
	 * the other hand, even without -F, if the pattern does not
	 * have any regexp special characters and there is no need for
	 * case-folding search, we can internally turn it into a
	 * simple string match using kws.  p->fixed tells us if we
	 * want to use kws.
	 */
	if (opt->fixed ||
	    has_null(p->pattern, p->patternlen) ||
	    is_fixed(p->pattern, p->patternlen))
		p->fixed = !p->ignore_case || ascii_only;

	if (p->fixed) {
		p->kws = kwsalloc(p->ignore_case ? tolower_trans_tbl : NULL);
		kwsincr(p->kws, p->pattern, p->patternlen);
		kwsprep(p->kws);
		return;
	} else if (opt->fixed) {
		/*
		 * We come here when the pattern has the non-ascii
		 * characters we cannot case-fold, and asked to
		 * ignore-case.
		 */
		compile_fixed_regexp(p, opt);
		return;
	}

	if (opt->pcre2) {
		compile_pcre2_pattern(p, opt);
		return;
	}

	if (opt->pcre1) {
		compile_pcre1_regexp(p, opt);
		return;
	}

	if (p->ignore_case)
		regflags |= REG_ICASE;
	if (opt->extended_regexp_option)
		regflags |= REG_EXTENDED;
	err = regcomp(&p->regexp, p->pattern, regflags);
	if (err) {
		char errbuf[1024];
		regerror(err, &p->regexp, errbuf, 1024);
		compile_regexp_failed(p, errbuf);
	}
}