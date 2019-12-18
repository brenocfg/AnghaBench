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
typedef  int /*<<< orphan*/  git_filter_source ;
typedef  int /*<<< orphan*/  const git_filter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (void*) ; 
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 void* git__strdup (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int wildcard_filter_check(
	git_filter  *self,
	void **payload,
	const git_filter_source *src,
	const char **attr_values)
{
	GIT_UNUSED(self);
	GIT_UNUSED(src);

	if (strcmp(attr_values[0], "wcflip") == 0 ||
		strcmp(attr_values[0], "wcreverse") == 0) {
		*payload = git__strdup(attr_values[0]);
		GIT_ERROR_CHECK_ALLOC(*payload);
		return 0;
	}

	return GIT_PASSTHROUGH;
}