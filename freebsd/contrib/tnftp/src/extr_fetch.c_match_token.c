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
 int /*<<< orphan*/  ISLWS (char const) ; 
 int /*<<< orphan*/  SKIPLWS (char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

__attribute__((used)) static const char *
match_token(const char **buf, const char *token)
{
	const char	*p, *orig;
	size_t		tlen;

	tlen = strlen(token);
	p = *buf;
	SKIPLWS(p);
	orig = p;
	if (strncasecmp(p, token, tlen) != 0)
		return NULL;
	p += tlen;
	if (*p != '\0' && !ISLWS(*p))
		return NULL;
	SKIPLWS(p);
	orig = *buf;
	*buf = p;
	return orig;
}