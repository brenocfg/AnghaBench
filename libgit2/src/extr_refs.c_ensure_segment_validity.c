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
 int /*<<< orphan*/  GIT_FILELOCK_EXTENSION ; 
 int /*<<< orphan*/  is_valid_ref_char (char const) ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ensure_segment_validity(const char *name, char may_contain_glob)
{
	const char *current = name;
	char prev = '\0';
	const int lock_len = (int)strlen(GIT_FILELOCK_EXTENSION);
	int segment_len;

	if (*current == '.')
		return -1; /* Refname starts with "." */

	for (current = name; ; current++) {
		if (*current == '\0' || *current == '/')
			break;

		if (!is_valid_ref_char(*current))
			return -1; /* Illegal character in refname */

		if (prev == '.' && *current == '.')
			return -1; /* Refname contains ".." */

		if (prev == '@' && *current == '{')
			return -1; /* Refname contains "@{" */

		if (*current == '*') {
			if (!may_contain_glob)
				return -1;
			may_contain_glob = 0;
		}

		prev = *current;
	}

	segment_len = (int)(current - name);

	/* A refname component can not end with ".lock" */
	if (segment_len >= lock_len &&
		!memcmp(current - lock_len, GIT_FILELOCK_EXTENSION, lock_len))
			return -1;

	return segment_len;
}