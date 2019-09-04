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
 scalar_t__ GIT_ADD_SIZET_OVERFLOW (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__malloc (size_t) ; 
 int /*<<< orphan*/ * git_config_escaped ; 
 char* git_config_escapes ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 char* strchr (char*,char const) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int unescape_line(
	char **out, bool *is_multi, const char *ptr, int quote_count)
{
	char *str, *fixed, *esc;
	size_t ptr_len = strlen(ptr), alloc_len;

	*is_multi = false;

	if (GIT_ADD_SIZET_OVERFLOW(&alloc_len, ptr_len, 1) ||
		(str = git__malloc(alloc_len)) == NULL) {
		return -1;
	}

	fixed = str;

	while (*ptr != '\0') {
		if (*ptr == '"') {
			quote_count++;
		} else if (*ptr != '\\') {
			*fixed++ = *ptr;
		} else {
			/* backslash, check the next char */
			ptr++;
			/* if we're at the end, it's a multiline, so keep the backslash */
			if (*ptr == '\0') {
				*is_multi = true;
				goto done;
			}
			if ((esc = strchr(git_config_escapes, *ptr)) != NULL) {
				*fixed++ = git_config_escaped[esc - git_config_escapes];
			} else {
				git__free(str);
				git_error_set(GIT_ERROR_CONFIG, "invalid escape at %s", ptr);
				return -1;
			}
		}
		ptr++;
	}

done:
	*fixed = '\0';
	*out = str;

	return 0;
}