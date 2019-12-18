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
 int /*<<< orphan*/  S_ISLNK (unsigned int) ; 
 scalar_t__ is_dir_sep (char const) ; 
 int /*<<< orphan*/  skip_iprefix (char const*,char*,char const**) ; 

__attribute__((used)) static int verify_dotfile(const char *rest, unsigned mode)
{
	/*
	 * The first character was '.', but that
	 * has already been discarded, we now test
	 * the rest.
	 */

	/* "." is not allowed */
	if (*rest == '\0' || is_dir_sep(*rest))
		return 0;

	switch (*rest) {
	/*
	 * ".git" followed by NUL or slash is bad. Note that we match
	 * case-insensitively here, even if ignore_case is not set.
	 * This outlaws ".GIT" everywhere out of an abundance of caution,
	 * since there's really no good reason to allow it.
	 *
	 * Once we've seen ".git", we can also find ".gitmodules", etc (also
	 * case-insensitively).
	 */
	case 'g':
	case 'G':
		if (rest[1] != 'i' && rest[1] != 'I')
			break;
		if (rest[2] != 't' && rest[2] != 'T')
			break;
		if (rest[3] == '\0' || is_dir_sep(rest[3]))
			return 0;
		if (S_ISLNK(mode)) {
			rest += 3;
			if (skip_iprefix(rest, "modules", &rest) &&
			    (*rest == '\0' || is_dir_sep(*rest)))
				return 0;
		}
		break;
	case '.':
		if (rest[1] == '\0' || is_dir_sep(rest[1]))
			return 0;
	}
	return 1;
}