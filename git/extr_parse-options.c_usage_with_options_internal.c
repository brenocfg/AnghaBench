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
struct parse_opt_ctx_t {int flags; } ;
struct option {scalar_t__ type; char* help; int flags; int short_name; char* long_name; scalar_t__ value; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ OPTION_ALIAS ; 
 scalar_t__ OPTION_END ; 
 scalar_t__ OPTION_GROUP ; 
 scalar_t__ OPTION_NUMBER ; 
 int PARSE_OPT_HELP ; 
 int PARSE_OPT_HIDDEN ; 
 int PARSE_OPT_LITERAL_ARGHELP ; 
 int PARSE_OPT_NOARG ; 
 int PARSE_OPT_NODASH ; 
 int PARSE_OPT_SHELL_EVAL ; 
 char* USAGE_GAP ; 
 size_t USAGE_OPTS_WIDTH ; 
 char* _ (char const* const) ; 
 size_t fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ usage_argh (struct option const*,int /*<<< orphan*/ *) ; 
 scalar_t__ utf8_fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int usage_with_options_internal(struct parse_opt_ctx_t *ctx,
				       const char * const *usagestr,
				       const struct option *opts, int full, int err)
{
	FILE *outfile = err ? stderr : stdout;
	int need_newline;

	if (!usagestr)
		return PARSE_OPT_HELP;

	if (!err && ctx && ctx->flags & PARSE_OPT_SHELL_EVAL)
		fprintf(outfile, "cat <<\\EOF\n");

	fprintf_ln(outfile, _("usage: %s"), _(*usagestr++));
	while (*usagestr && **usagestr)
		/*
		 * TRANSLATORS: the colon here should align with the
		 * one in "usage: %s" translation.
		 */
		fprintf_ln(outfile, _("   or: %s"), _(*usagestr++));
	while (*usagestr) {
		if (**usagestr)
			fprintf_ln(outfile, _("    %s"), _(*usagestr));
		else
			fputc('\n', outfile);
		usagestr++;
	}

	need_newline = 1;

	for (; opts->type != OPTION_END; opts++) {
		size_t pos;
		int pad;

		if (opts->type == OPTION_GROUP) {
			fputc('\n', outfile);
			need_newline = 0;
			if (*opts->help)
				fprintf(outfile, "%s\n", _(opts->help));
			continue;
		}
		if (!full && (opts->flags & PARSE_OPT_HIDDEN))
			continue;

		if (need_newline) {
			fputc('\n', outfile);
			need_newline = 0;
		}

		pos = fprintf(outfile, "    ");
		if (opts->short_name) {
			if (opts->flags & PARSE_OPT_NODASH)
				pos += fprintf(outfile, "%c", opts->short_name);
			else
				pos += fprintf(outfile, "-%c", opts->short_name);
		}
		if (opts->long_name && opts->short_name)
			pos += fprintf(outfile, ", ");
		if (opts->long_name)
			pos += fprintf(outfile, "--%s", opts->long_name);
		if (opts->type == OPTION_NUMBER)
			pos += utf8_fprintf(outfile, _("-NUM"));

		if ((opts->flags & PARSE_OPT_LITERAL_ARGHELP) ||
		    !(opts->flags & PARSE_OPT_NOARG))
			pos += usage_argh(opts, outfile);

		if (pos <= USAGE_OPTS_WIDTH)
			pad = USAGE_OPTS_WIDTH - pos;
		else {
			fputc('\n', outfile);
			pad = USAGE_OPTS_WIDTH;
		}
		if (opts->type == OPTION_ALIAS) {
			fprintf(outfile, "%*s", pad + USAGE_GAP, "");
			fprintf_ln(outfile, _("alias of --%s"),
				   (const char *)opts->value);
			continue;
		}
		fprintf(outfile, "%*s%s\n", pad + USAGE_GAP, "", _(opts->help));
	}
	fputc('\n', outfile);

	if (!err && ctx && ctx->flags & PARSE_OPT_SHELL_EVAL)
		fputs("EOF\n", outfile);

	return PARSE_OPT_HELP;
}