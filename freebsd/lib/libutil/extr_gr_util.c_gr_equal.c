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
struct group {scalar_t__ gr_gid; int /*<<< orphan*/ ** gr_mem; int /*<<< orphan*/ * gr_passwd; int /*<<< orphan*/ * gr_name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
gr_equal(const struct group *gr1, const struct group *gr2)
{

	/* Check that the non-member information is the same. */
	if (gr1->gr_name == NULL || gr2->gr_name == NULL) {
		if (gr1->gr_name != gr2->gr_name)
			return (false);
	} else if (strcmp(gr1->gr_name, gr2->gr_name) != 0)
		return (false);
	if (gr1->gr_passwd == NULL || gr2->gr_passwd == NULL) {
		if (gr1->gr_passwd != gr2->gr_passwd)
			return (false);
	} else if (strcmp(gr1->gr_passwd, gr2->gr_passwd) != 0)
		return (false);
	if (gr1->gr_gid != gr2->gr_gid)
		return (false);

	/*
	 * Check all members in both groups.
	 * getgrnam can return gr_mem with a pointer to NULL.
	 * gr_dup and gr_add strip out this superfluous NULL, setting
	 * gr_mem to NULL for no members.
	*/
	if (gr1->gr_mem != NULL && gr2->gr_mem != NULL) {
		int i;

		for (i = 0;
		    gr1->gr_mem[i] != NULL && gr2->gr_mem[i] != NULL; i++) {
			if (strcmp(gr1->gr_mem[i], gr2->gr_mem[i]) != 0)
				return (false);
		}
		if (gr1->gr_mem[i] != NULL || gr2->gr_mem[i] != NULL)
			return (false);
	} else if (gr1->gr_mem != NULL && gr1->gr_mem[0] != NULL) {
		return (false);
	} else if (gr2->gr_mem != NULL && gr2->gr_mem[0] != NULL) {
		return (false);
	}

	return (true);
}