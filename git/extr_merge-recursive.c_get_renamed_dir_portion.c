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
 char* strrchr (char const*,char) ; 
 char* xstrdup (char*) ; 
 char* xstrndup (char const*,int) ; 

__attribute__((used)) static void get_renamed_dir_portion(const char *old_path, const char *new_path,
				    char **old_dir, char **new_dir)
{
	char *end_of_old, *end_of_new;

	/* Default return values: NULL, meaning no rename */
	*old_dir = NULL;
	*new_dir = NULL;

	/*
	 * For
	 *    "a/b/c/d/e/foo.c" -> "a/b/some/thing/else/e/foo.c"
	 * the "e/foo.c" part is the same, we just want to know that
	 *    "a/b/c/d" was renamed to "a/b/some/thing/else"
	 * so, for this example, this function returns "a/b/c/d" in
	 * *old_dir and "a/b/some/thing/else" in *new_dir.
	 */

	/*
	 * If the basename of the file changed, we don't care.  We want
	 * to know which portion of the directory, if any, changed.
	 */
	end_of_old = strrchr(old_path, '/');
	end_of_new = strrchr(new_path, '/');

	/*
	 * If end_of_old is NULL, old_path wasn't in a directory, so there
	 * could not be a directory rename (our rule elsewhere that a
	 * directory which still exists is not considered to have been
	 * renamed means the root directory can never be renamed -- because
	 * the root directory always exists).
	 */
	if (end_of_old == NULL)
		return; /* Note: *old_dir and *new_dir are still NULL */

	/*
	 * If new_path contains no directory (end_of_new is NULL), then we
	 * have a rename of old_path's directory to the root directory.
	 */
	if (end_of_new == NULL) {
		*old_dir = xstrndup(old_path, end_of_old - old_path);
		*new_dir = xstrdup("");
		return;
	}

	/* Find the first non-matching character traversing backwards */
	while (*--end_of_new == *--end_of_old &&
	       end_of_old != old_path &&
	       end_of_new != new_path)
		; /* Do nothing; all in the while loop */

	/*
	 * If both got back to the beginning of their strings, then the
	 * directory didn't change at all, only the basename did.
	 */
	if (end_of_old == old_path && end_of_new == new_path &&
	    *end_of_old == *end_of_new)
		return; /* Note: *old_dir and *new_dir are still NULL */

	/*
	 * If end_of_new got back to the beginning of its string, and
	 * end_of_old got back to the beginning of some subdirectory, then
	 * we have a rename/merge of a subdirectory into the root, which
	 * needs slightly special handling.
	 *
	 * Note: There is no need to consider the opposite case, with a
	 * rename/merge of the root directory into some subdirectory
	 * because as noted above the root directory always exists so it
	 * cannot be considered to be renamed.
	 */
	if (end_of_new == new_path &&
	    end_of_old != old_path && end_of_old[-1] == '/') {
		*old_dir = xstrndup(old_path, --end_of_old - old_path);
		*new_dir = xstrdup("");
		return;
	}

	/*
	 * We've found the first non-matching character in the directory
	 * paths.  That means the current characters we were looking at
	 * were part of the first non-matching subdir name going back from
	 * the end of the strings.  Get the whole name by advancing both
	 * end_of_old and end_of_new to the NEXT '/' character.  That will
	 * represent the entire directory rename.
	 *
	 * The reason for the increment is cases like
	 *    a/b/star/foo/whatever.c -> a/b/tar/foo/random.c
	 * After dropping the basename and going back to the first
	 * non-matching character, we're now comparing:
	 *    a/b/s          and         a/b/
	 * and we want to be comparing:
	 *    a/b/star/      and         a/b/tar/
	 * but without the pre-increment, the one on the right would stay
	 * a/b/.
	 */
	end_of_old = strchr(++end_of_old, '/');
	end_of_new = strchr(++end_of_new, '/');

	/* Copy the old and new directories into *old_dir and *new_dir. */
	*old_dir = xstrndup(old_path, end_of_old - old_path);
	*new_dir = xstrndup(new_path, end_of_new - new_path);
}