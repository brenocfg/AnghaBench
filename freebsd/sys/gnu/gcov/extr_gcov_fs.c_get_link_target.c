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
struct gcov_link {scalar_t__ dir; int /*<<< orphan*/  ext; } ;

/* Variables and functions */
 scalar_t__ SRC_TREE ; 
 char* link_target (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * objtree ; 
 int /*<<< orphan*/ * srctree ; 
 int strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
get_link_target(const char *filename, const struct gcov_link *ext)
{
	const char *rel;
	char *result;

	if (strncmp(filename, objtree, strlen(objtree)) == 0) {
		rel = filename + strlen(objtree) + 1;
		if (ext->dir == SRC_TREE)
			result = link_target(srctree, rel, ext->ext);
		else
			result = link_target(objtree, rel, ext->ext);
	} else {
		/* External compilation. */
		result = link_target(NULL, filename, ext->ext);
	}

	return (result);
}