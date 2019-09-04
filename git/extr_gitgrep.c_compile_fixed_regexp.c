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
struct strbuf {char* buf; } ;
struct grep_pat {int /*<<< orphan*/  regexp; int /*<<< orphan*/  pattern; } ;
struct grep_opt {scalar_t__ debug; scalar_t__ ignore_case; } ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int REG_ICASE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  basic_regex_quote_buf (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_regexp_failed (struct grep_pat*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void compile_fixed_regexp(struct grep_pat *p, struct grep_opt *opt)
{
	struct strbuf sb = STRBUF_INIT;
	int err;
	int regflags = 0;

	basic_regex_quote_buf(&sb, p->pattern);
	if (opt->ignore_case)
		regflags |= REG_ICASE;
	err = regcomp(&p->regexp, sb.buf, regflags);
	if (opt->debug)
		fprintf(stderr, "fixed %s\n", sb.buf);
	strbuf_release(&sb);
	if (err) {
		char errbuf[1024];
		regerror(err, &p->regexp, errbuf, sizeof(errbuf));
		compile_regexp_failed(p, errbuf);
	}
}