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

/* Variables and functions */
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  need_bs_quote (char) ; 

__attribute__((used)) static char *sq_dequote_step(char *arg, char **next)
{
	char *dst = arg;
	char *src = arg;
	char c;

	if (*src != '\'')
		return NULL;
	for (;;) {
		c = *++src;
		if (!c)
			return NULL;
		if (c != '\'') {
			*dst++ = c;
			continue;
		}
		/* We stepped out of sq */
		switch (*++src) {
		case '\0':
			*dst = 0;
			if (next)
				*next = NULL;
			return arg;
		case '\\':
			/*
			 * Allow backslashed characters outside of
			 * single-quotes only if they need escaping,
			 * and only if we resume the single-quoted part
			 * afterward.
			 */
			if (need_bs_quote(src[1]) && src[2] == '\'') {
				*dst++ = src[1];
				src += 2;
				continue;
			}
		/* Fallthrough */
		default:
			if (!next || !isspace(*src))
				return NULL;
			do {
				c = *++src;
			} while (isspace(c));
			*dst = 0;
			*next = src;
			return arg;
		}
	}
}