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
struct group {scalar_t__ gr_gid; int /*<<< orphan*/  gr_mem; int /*<<< orphan*/ * gr_passwd; int /*<<< orphan*/ * gr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  group_mem_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
group_compare(const struct group *grp0, const struct group *grp1)
{

	if (grp0 == NULL && grp1 == NULL)
		return (true);
	if (grp0 == NULL || grp1 == NULL)
		return (false);

	if (strcmp(grp0->gr_name, grp1->gr_name) != 0)
		return (false);

	if (grp0->gr_passwd != NULL || grp1->gr_passwd != NULL) {
		if (grp0->gr_passwd == NULL || grp1->gr_passwd == NULL)
			return (false);
		if (strcmp(grp0->gr_passwd, grp1->gr_passwd) != 0)
			return (false);
	}

	if (grp0->gr_gid != grp1->gr_gid)
		return (false);

	if (!group_mem_compare(grp0->gr_mem, grp1->gr_mem))
		return (false);

	return (true);
}