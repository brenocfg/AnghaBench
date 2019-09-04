#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grep_opt {scalar_t__ last_shown; char const** colors; int /*<<< orphan*/  (* output ) (struct grep_opt*,char*,int) ;scalar_t__ only_matching; scalar_t__ color; scalar_t__ show_hunk_mark; scalar_t__ funcbody; scalar_t__ post_context; scalar_t__ pre_context; scalar_t__ file_break; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  enum grep_context { ____Placeholder_grep_context } grep_context ;

/* Variables and functions */
 size_t GREP_COLOR_CONTEXT ; 
 size_t GREP_COLOR_FUNCTION ; 
 size_t GREP_COLOR_MATCH_CONTEXT ; 
 size_t GREP_COLOR_MATCH_SELECTED ; 
 size_t GREP_COLOR_SELECTED ; 
 size_t GREP_COLOR_SEP ; 
 int GREP_CONTEXT_BODY ; 
 int REG_NOTBOL ; 
 scalar_t__ next_match (struct grep_opt*,char*,char*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  output_color (struct grep_opt*,char*,int,char const*) ; 
 int /*<<< orphan*/  show_line_header (struct grep_opt*,char const*,unsigned int,int,char) ; 
 int /*<<< orphan*/  stub1 (struct grep_opt*,char*,int) ; 
 int /*<<< orphan*/  stub2 (struct grep_opt*,char*,int) ; 
 int /*<<< orphan*/  stub3 (struct grep_opt*,char*,int) ; 
 int /*<<< orphan*/  stub4 (struct grep_opt*,char*,int) ; 
 int /*<<< orphan*/  stub5 (struct grep_opt*,char*,int) ; 

__attribute__((used)) static void show_line(struct grep_opt *opt, char *bol, char *eol,
		      const char *name, unsigned lno, ssize_t cno, char sign)
{
	int rest = eol - bol;
	const char *match_color = NULL;
	const char *line_color = NULL;

	if (opt->file_break && opt->last_shown == 0) {
		if (opt->show_hunk_mark)
			opt->output(opt, "\n", 1);
	} else if (opt->pre_context || opt->post_context || opt->funcbody) {
		if (opt->last_shown == 0) {
			if (opt->show_hunk_mark) {
				output_color(opt, "--", 2, opt->colors[GREP_COLOR_SEP]);
				opt->output(opt, "\n", 1);
			}
		} else if (lno > opt->last_shown + 1) {
			output_color(opt, "--", 2, opt->colors[GREP_COLOR_SEP]);
			opt->output(opt, "\n", 1);
		}
	}
	if (!opt->only_matching) {
		/*
		 * In case the line we're being called with contains more than
		 * one match, leave printing each header to the loop below.
		 */
		show_line_header(opt, name, lno, cno, sign);
	}
	if (opt->color || opt->only_matching) {
		regmatch_t match;
		enum grep_context ctx = GREP_CONTEXT_BODY;
		int ch = *eol;
		int eflags = 0;

		if (opt->color) {
			if (sign == ':')
				match_color = opt->colors[GREP_COLOR_MATCH_SELECTED];
			else
				match_color = opt->colors[GREP_COLOR_MATCH_CONTEXT];
			if (sign == ':')
				line_color = opt->colors[GREP_COLOR_SELECTED];
			else if (sign == '-')
				line_color = opt->colors[GREP_COLOR_CONTEXT];
			else if (sign == '=')
				line_color = opt->colors[GREP_COLOR_FUNCTION];
		}
		*eol = '\0';
		while (next_match(opt, bol, eol, ctx, &match, eflags)) {
			if (match.rm_so == match.rm_eo)
				break;

			if (opt->only_matching)
				show_line_header(opt, name, lno, cno, sign);
			else
				output_color(opt, bol, match.rm_so, line_color);
			output_color(opt, bol + match.rm_so,
				     match.rm_eo - match.rm_so, match_color);
			if (opt->only_matching)
				opt->output(opt, "\n", 1);
			bol += match.rm_eo;
			cno += match.rm_eo;
			rest -= match.rm_eo;
			eflags = REG_NOTBOL;
		}
		*eol = ch;
	}
	if (!opt->only_matching) {
		output_color(opt, bol, rest, line_color);
		opt->output(opt, "\n", 1);
	}
}