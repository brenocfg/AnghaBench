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
 int /*<<< orphan*/  strncasecmp (char const*,char const*,int) ; 
 char const tolower (char const) ; 

__attribute__((used)) static int is_ntfs_dot_generic(const char *name,
			       const char *dotgit_name,
			       size_t len,
			       const char *dotgit_ntfs_shortname_prefix)
{
	int saw_tilde;
	size_t i;

	if ((name[0] == '.' && !strncasecmp(name + 1, dotgit_name, len))) {
		i = len + 1;
only_spaces_and_periods:
		for (;;) {
			char c = name[i++];
			if (!c)
				return 1;
			if (c != ' ' && c != '.')
				return 0;
		}
	}

	/*
	 * Is it a regular NTFS short name, i.e. shortened to 6 characters,
	 * followed by ~1, ... ~4?
	 */
	if (!strncasecmp(name, dotgit_name, 6) && name[6] == '~' &&
	    name[7] >= '1' && name[7] <= '4') {
		i = 8;
		goto only_spaces_and_periods;
	}

	/*
	 * Is it a fall-back NTFS short name (for details, see
	 * https://en.wikipedia.org/wiki/8.3_filename?
	 */
	for (i = 0, saw_tilde = 0; i < 8; i++)
		if (name[i] == '\0')
			return 0;
		else if (saw_tilde) {
			if (name[i] < '0' || name[i] > '9')
				return 0;
		} else if (name[i] == '~') {
			if (name[++i] < '1' || name[i] > '9')
				return 0;
			saw_tilde = 1;
		} else if (i >= 6)
			return 0;
		else if (name[i] & 0x80) {
			/*
			 * We know our needles contain only ASCII, so we clamp
			 * here to make the results of tolower() sane.
			 */
			return 0;
		} else if (tolower(name[i]) != dotgit_ntfs_shortname_prefix[i])
			return 0;

	goto only_spaces_and_periods;
}