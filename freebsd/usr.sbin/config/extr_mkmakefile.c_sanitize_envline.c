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
 scalar_t__ isspace (char) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void
sanitize_envline(char *result, const char *src)
{
	const char *eq;
	char c, *dst;
	bool leading;

	/* If there is no '=' it's not a well-formed name=value line. */
	if ((eq = strchr(src, '=')) == NULL) {
		*result = 0;
		return;
	}
	dst = result;

	/* Copy chars before the '=', skipping any leading spaces/quotes. */
	leading = true;
	while (src < eq) {
		c = *src++;
		if (leading && (isspace(c) || c == '"'))
			continue;
		*dst++ = c;
		leading = false;
	}

	/* If it was all leading space, we don't have a well-formed line. */
	if (leading) {
		*result = 0;
		return;
	}

	/* Trim spaces/quotes immediately before the '=', then copy the '='. */
	while (isspace(dst[-1]) || dst[-1] == '"')
		--dst;
	*dst++ = *src++;

	/* Copy chars after the '=', skipping any leading whitespace. */
	leading = true;
	while ((c = *src++) != 0) {
		if (leading && (isspace(c) || c == '"'))
			continue;
		*dst++ = c;
		leading = false;
	}

	/* If it was all leading space, it's a valid 'var=' (nil value). */
	if (leading) {
		*dst = 0;
		return;
	}

	/* Trim trailing whitespace and quotes. */
	while (isspace(dst[-1]) || dst[-1] == '"')
		--dst;

	*dst = 0;
}