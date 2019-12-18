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
 scalar_t__ abspath_part_inside_repo (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_absolute_path (char const*) ; 
 scalar_t__ normalize_path_copy_len (char*,char const*,int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* xmallocz (int /*<<< orphan*/ ) ; 
 char* xstrfmt (char*,int,char const*,char const*) ; 

char *prefix_path_gently(const char *prefix, int len,
			 int *remaining_prefix, const char *path)
{
	const char *orig = path;
	char *sanitized;
	if (is_absolute_path(orig)) {
		sanitized = xmallocz(strlen(path));
		if (remaining_prefix)
			*remaining_prefix = 0;
		if (normalize_path_copy_len(sanitized, path, remaining_prefix)) {
			free(sanitized);
			return NULL;
		}
		if (abspath_part_inside_repo(sanitized)) {
			free(sanitized);
			return NULL;
		}
	} else {
		sanitized = xstrfmt("%.*s%s", len, len ? prefix : "", path);
		if (remaining_prefix)
			*remaining_prefix = len;
		if (normalize_path_copy_len(sanitized, sanitized, remaining_prefix)) {
			free(sanitized);
			return NULL;
		}
	}
	return sanitized;
}