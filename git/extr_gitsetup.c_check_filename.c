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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_missing_file_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstat (char const*,struct stat*) ; 
 char* prefix_filename (char const*,char const*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 

int check_filename(const char *prefix, const char *arg)
{
	char *to_free = NULL;
	struct stat st;

	if (skip_prefix(arg, ":/", &arg)) {
		if (!*arg) /* ":/" is root dir, always exists */
			return 1;
		prefix = NULL;
	} else if (skip_prefix(arg, ":!", &arg) ||
		   skip_prefix(arg, ":^", &arg)) {
		if (!*arg) /* excluding everything is silly, but allowed */
			return 1;
	}

	if (prefix)
		arg = to_free = prefix_filename(prefix, arg);

	if (!lstat(arg, &st)) {
		free(to_free);
		return 1; /* file exists */
	}
	if (is_missing_file_error(errno)) {
		free(to_free);
		return 0; /* file does not exist */
	}
	die_errno(_("failed to stat '%s'"), arg);
}