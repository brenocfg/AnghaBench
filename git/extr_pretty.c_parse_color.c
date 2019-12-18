#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct format_commit_context {TYPE_1__* pretty_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int COLOR_MAXLEN ; 
 char* GIT_COLOR_BLUE ; 
 char* GIT_COLOR_GREEN ; 
 char* GIT_COLOR_RED ; 
 char* GIT_COLOR_RESET ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ color_parse_mem (char const*,int,char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ want_color (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t parse_color(struct strbuf *sb, /* in UTF-8 */
			  const char *placeholder,
			  struct format_commit_context *c)
{
	const char *rest = placeholder;
	const char *basic_color = NULL;

	if (placeholder[1] == '(') {
		const char *begin = placeholder + 2;
		const char *end = strchr(begin, ')');
		char color[COLOR_MAXLEN];

		if (!end)
			return 0;

		if (skip_prefix(begin, "auto,", &begin)) {
			if (!want_color(c->pretty_ctx->color))
				return end - placeholder + 1;
		} else if (skip_prefix(begin, "always,", &begin)) {
			/* nothing to do; we do not respect want_color at all */
		} else {
			/* the default is the same as "auto" */
			if (!want_color(c->pretty_ctx->color))
				return end - placeholder + 1;
		}

		if (color_parse_mem(begin, end - begin, color) < 0)
			die(_("unable to parse --pretty format"));
		strbuf_addstr(sb, color);
		return end - placeholder + 1;
	}

	/*
	 * We handle things like "%C(red)" above; for historical reasons, there
	 * are a few colors that can be specified without parentheses (and
	 * they cannot support things like "auto" or "always" at all).
	 */
	if (skip_prefix(placeholder + 1, "red", &rest))
		basic_color = GIT_COLOR_RED;
	else if (skip_prefix(placeholder + 1, "green", &rest))
		basic_color = GIT_COLOR_GREEN;
	else if (skip_prefix(placeholder + 1, "blue", &rest))
		basic_color = GIT_COLOR_BLUE;
	else if (skip_prefix(placeholder + 1, "reset", &rest))
		basic_color = GIT_COLOR_RESET;

	if (basic_color && want_color(c->pretty_ctx->color))
		strbuf_addstr(sb, basic_color);

	return rest - placeholder;
}