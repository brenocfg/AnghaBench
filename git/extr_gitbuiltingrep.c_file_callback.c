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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct option {struct grep_opt* value; } ;
struct grep_opt {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  GREP_PATTERN ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  append_grep_pat (struct grep_opt*,int /*<<< orphan*/ ,scalar_t__,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int file_callback(const struct option *opt, const char *arg, int unset)
{
	struct grep_opt *grep_opt = opt->value;
	int from_stdin;
	FILE *patterns;
	int lno = 0;
	struct strbuf sb = STRBUF_INIT;

	BUG_ON_OPT_NEG(unset);

	from_stdin = !strcmp(arg, "-");
	patterns = from_stdin ? stdin : fopen(arg, "r");
	if (!patterns)
		die_errno(_("cannot open '%s'"), arg);
	while (strbuf_getline(&sb, patterns) == 0) {
		/* ignore empty line like grep does */
		if (sb.len == 0)
			continue;

		append_grep_pat(grep_opt, sb.buf, sb.len, arg, ++lno,
				GREP_PATTERN);
	}
	if (!from_stdin)
		fclose(patterns);
	strbuf_release(&sb);
	return 0;
}