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
struct group {int /*<<< orphan*/ ** gr_mem; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bool
grp_has_member(struct group *grp, const char *name)
{
	int j;

	for (j = 0; grp->gr_mem != NULL && grp->gr_mem[j] != NULL; j++)
		if (strcmp(grp->gr_mem[j], name) == 0)
			return (true);
	return (false);
}