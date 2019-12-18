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
 int PATHMATCH_NO_ANCHOR_END ; 
 int /*<<< orphan*/  archive_pathmatch (char const*,char const*,int) ; 
 int /*<<< orphan*/  pm_list (char const*,char const*,char const,int) ; 
 char* pm_slashskip (char const*) ; 

__attribute__((used)) static int
pm(const char *p, const char *s, int flags)
{
	const char *end;

	/*
	 * Ignore leading './', './/', '././', etc.
	 */
	if (s[0] == '.' && s[1] == '/')
		s = pm_slashskip(s + 1);
	if (p[0] == '.' && p[1] == '/')
		p = pm_slashskip(p + 1);

	for (;;) {
		switch (*p) {
		case '\0':
			if (s[0] == '/') {
				if (flags & PATHMATCH_NO_ANCHOR_END)
					return (1);
				/* "dir" == "dir/" == "dir/." */
				s = pm_slashskip(s);
			}
			return (*s == '\0');
		case '?':
			/* ? always succeeds, unless we hit end of 's' */
			if (*s == '\0')
				return (0);
			break;
		case '*':
			/* "*" == "**" == "***" ... */
			while (*p == '*')
				++p;
			/* Trailing '*' always succeeds. */
			if (*p == '\0')
				return (1);
			while (*s) {
				if (archive_pathmatch(p, s, flags))
					return (1);
				++s;
			}
			return (0);
		case '[':
			/*
			 * Find the end of the [...] character class,
			 * ignoring \] that might occur within the class.
			 */
			end = p + 1;
			while (*end != '\0' && *end != ']') {
				if (*end == '\\' && end[1] != '\0')
					++end;
				++end;
			}
			if (*end == ']') {
				/* We found [...], try to match it. */
				if (!pm_list(p + 1, end, *s, flags))
					return (0);
				p = end; /* Jump to trailing ']' char. */
				break;
			} else
				/* No final ']', so just match '['. */
				if (*p != *s)
					return (0);
			break;
		case '\\':
			/* Trailing '\\' matches itself. */
			if (p[1] == '\0') {
				if (*s != '\\')
					return (0);
			} else {
				++p;
				if (*p != *s)
					return (0);
			}
			break;
		case '/':
			if (*s != '/' && *s != '\0')
				return (0);
			/* Note: pattern "/\./" won't match "/";
			 * pm_slashskip() correctly stops at backslash. */
			p = pm_slashskip(p);
			s = pm_slashskip(s);
			if (*p == '\0' && (flags & PATHMATCH_NO_ANCHOR_END))
				return (1);
			--p; /* Counteract the increment below. */
			--s;
			break;
		case '$':
			/* '$' is special only at end of pattern and only
			 * if PATHMATCH_NO_ANCHOR_END is specified. */
			if (p[1] == '\0' && (flags & PATHMATCH_NO_ANCHOR_END)){
				/* "dir" == "dir/" == "dir/." */
				return (*pm_slashskip(s) == '\0');
			}
			/* Otherwise, '$' is not special. */
			/* FALL THROUGH */
		default:
			if (*p != *s)
				return (0);
			break;
		}
		++p;
		++s;
	}
}