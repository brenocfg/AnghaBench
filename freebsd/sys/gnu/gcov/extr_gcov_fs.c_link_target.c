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
 int /*<<< orphan*/  M_GCOV ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  asprintf (char**,int /*<<< orphan*/ ,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* strdup_flags (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *
link_target(const char *dir, const char *path, const char *ext)
{
	char *target;
	char *old_ext;
	char *copy;

	copy = strdup_flags(path, M_GCOV, M_NOWAIT);
	if (!copy)
		return (NULL);
	old_ext = strrchr(copy, '.');
	if (old_ext)
		*old_ext = '\0';
	target = NULL;
	if (dir)
		asprintf(&target, M_GCOV, "%s/%s.%s", dir, copy, ext);
	else
		asprintf(&target, M_GCOV, "%s.%s", copy, ext);
	free(copy, M_GCOV);

	return (target);
}