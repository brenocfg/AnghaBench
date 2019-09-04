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
 int /*<<< orphan*/  ALLOC_ARRAY (char const**,int) ; 
 unsigned int DUP_BASENAME ; 
 unsigned int KEEP_TRAILING_SLASH ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_dir_sep (char const) ; 
 char* prefix_path (char const*,int,char const*) ; 
 int strlen (char const*) ; 
 char* xmemdupz (char const*,int) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char **internal_prefix_pathspec(const char *prefix,
					     const char **pathspec,
					     int count, unsigned flags)
{
	int i;
	const char **result;
	int prefixlen = prefix ? strlen(prefix) : 0;
	ALLOC_ARRAY(result, count + 1);

	/* Create an intermediate copy of the pathspec based on the flags */
	for (i = 0; i < count; i++) {
		int length = strlen(pathspec[i]);
		int to_copy = length;
		char *it;
		while (!(flags & KEEP_TRAILING_SLASH) &&
		       to_copy > 0 && is_dir_sep(pathspec[i][to_copy - 1]))
			to_copy--;

		it = xmemdupz(pathspec[i], to_copy);
		if (flags & DUP_BASENAME) {
			result[i] = xstrdup(basename(it));
			free(it);
		} else {
			result[i] = it;
		}
	}
	result[count] = NULL;

	/* Prefix the pathspec and free the old intermediate strings */
	for (i = 0; i < count; i++) {
		const char *match = prefix_path(prefix, prefixlen, result[i]);
		free((char *) result[i]);
		result[i] = match;
	}

	return result;
}