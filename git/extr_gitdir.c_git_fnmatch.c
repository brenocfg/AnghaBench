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
struct pathspec_item {int flags; int magic; } ;

/* Variables and functions */
 int PATHSPEC_GLOB ; 
 int PATHSPEC_ICASE ; 
 int PATHSPEC_ONESTAR ; 
 int WM_CASEFOLD ; 
 int WM_NOMATCH ; 
 int WM_PATHNAME ; 
 scalar_t__ ps_strcmp (struct pathspec_item const*,char const*,char const*) ; 
 scalar_t__ ps_strncmp (struct pathspec_item const*,char const*,char const*,int) ; 
 int strlen (char const*) ; 
 int wildmatch (char const*,char const*,int) ; 

int git_fnmatch(const struct pathspec_item *item,
		const char *pattern, const char *string,
		int prefix)
{
	if (prefix > 0) {
		if (ps_strncmp(item, pattern, string, prefix))
			return WM_NOMATCH;
		pattern += prefix;
		string += prefix;
	}
	if (item->flags & PATHSPEC_ONESTAR) {
		int pattern_len = strlen(++pattern);
		int string_len = strlen(string);
		return string_len < pattern_len ||
			ps_strcmp(item, pattern,
				  string + string_len - pattern_len);
	}
	if (item->magic & PATHSPEC_GLOB)
		return wildmatch(pattern, string,
				 WM_PATHNAME |
				 (item->magic & PATHSPEC_ICASE ? WM_CASEFOLD : 0));
	else
		/* wildmatch has not learned no FNM_PATHNAME mode yet */
		return wildmatch(pattern, string,
				 item->magic & PATHSPEC_ICASE ? WM_CASEFOLD : 0);
}