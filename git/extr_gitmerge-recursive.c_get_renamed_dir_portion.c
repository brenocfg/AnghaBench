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
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 char* strrchr (char const*,char) ; 
 char* xstrndup (char const*,int) ; 

__attribute__((used)) static void get_renamed_dir_portion(const char *old_path, const char *new_path,
				    char **old_dir, char **new_dir)
{
	char *end_of_old, *end_of_new;
	int old_len, new_len;

	*old_dir = NULL;
	*new_dir = NULL;

	/*
	 * For
	 *    "a/b/c/d/e/foo.c" -> "a/b/some/thing/else/e/foo.c"
	 * the "e/foo.c" part is the same, we just want to know that
	 *    "a/b/c/d" was renamed to "a/b/some/thing/else"
	 * so, for this example, this function returns "a/b/c/d" in
	 * *old_dir and "a/b/some/thing/else" in *new_dir.
	 *
	 * Also, if the basename of the file changed, we don't care.  We
	 * want to know which portion of the directory, if any, changed.
	 */
	end_of_old = strrchr(old_path, '/');
	end_of_new = strrchr(new_path, '/');

	if (end_of_old == NULL || end_of_new == NULL)
		return;
	while (*--end_of_new == *--end_of_old &&
	       end_of_old != old_path &&
	       end_of_new != new_path)
		; /* Do nothing; all in the while loop */
	/*
	 * We've found the first non-matching character in the directory
	 * paths.  That means the current directory we were comparing
	 * represents the rename.  Move end_of_old and end_of_new back
	 * to the full directory name.
	 */
	if (*end_of_old == '/')
		end_of_old++;
	if (*end_of_old != '/')
		end_of_new++;
	end_of_old = strchr(end_of_old, '/');
	end_of_new = strchr(end_of_new, '/');

	/*
	 * It may have been the case that old_path and new_path were the same
	 * directory all along.  Don't claim a rename if they're the same.
	 */
	old_len = end_of_old - old_path;
	new_len = end_of_new - new_path;

	if (old_len != new_len || strncmp(old_path, new_path, old_len)) {
		*old_dir = xstrndup(old_path, old_len);
		*new_dir = xstrndup(new_path, new_len);
	}
}