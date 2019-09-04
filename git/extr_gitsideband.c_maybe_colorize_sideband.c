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
struct keyword_entry {int /*<<< orphan*/  color; int /*<<< orphan*/  keyword; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct keyword_entry*) ; 
 int /*<<< orphan*/  GIT_COLOR_RESET ; 
 int /*<<< orphan*/  isalnum (char const) ; 
 scalar_t__ isspace (char const) ; 
 struct keyword_entry* keywords ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char const) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  use_sideband_colors () ; 
 int /*<<< orphan*/  want_color_stderr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void maybe_colorize_sideband(struct strbuf *dest, const char *src, int n)
{
	int i;

	if (!want_color_stderr(use_sideband_colors())) {
		strbuf_add(dest, src, n);
		return;
	}

	while (0 < n && isspace(*src)) {
		strbuf_addch(dest, *src);
		src++;
		n--;
	}

	for (i = 0; i < ARRAY_SIZE(keywords); i++) {
		struct keyword_entry *p = keywords + i;
		int len = strlen(p->keyword);

		if (n < len)
			continue;
		/*
		 * Match case insensitively, so we colorize output from existing
		 * servers regardless of the case that they use for their
		 * messages. We only highlight the word precisely, so
		 * "successful" stays uncolored.
		 */
		if (!strncasecmp(p->keyword, src, len) &&
		    (len == n || !isalnum(src[len]))) {
			strbuf_addstr(dest, p->color);
			strbuf_add(dest, src, len);
			strbuf_addstr(dest, GIT_COLOR_RESET);
			n -= len;
			src += len;
			break;
		}
	}

	strbuf_add(dest, src, n);
}