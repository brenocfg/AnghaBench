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
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__strdup (char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ normalize_section (char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 

int git_config__normalize_name(const char *in, char **out)
{
	char *name, *fdot, *ldot;

	assert(in && out);

	name = git__strdup(in);
	GIT_ERROR_CHECK_ALLOC(name);

	fdot = strchr(name, '.');
	ldot = strrchr(name, '.');

	if (fdot == NULL || fdot == name || ldot == NULL || !ldot[1])
		goto invalid;

	/* Validate and downcase up to first dot and after last dot */
	if (normalize_section(name, fdot) < 0 ||
	    normalize_section(ldot + 1, NULL) < 0)
		goto invalid;

	/* If there is a middle range, make sure it doesn't have newlines */
	while (fdot < ldot)
		if (*fdot++ == '\n')
			goto invalid;

	*out = name;
	return 0;

invalid:
	git__free(name);
	git_error_set(GIT_ERROR_CONFIG, "invalid config item name '%s'", in);
	return GIT_EINVALIDSPEC;
}