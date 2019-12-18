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
typedef  int /*<<< orphan*/  uint32_t ;
struct genl_family_grp {int /*<<< orphan*/  list; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct genl_family {int /*<<< orphan*/  gf_mc_grps; } ;

/* Variables and functions */
 scalar_t__ GENL_NAMSIZ ; 
 int NLE_NOMEM ; 
 struct genl_family_grp* calloc (int,int) ; 
 int /*<<< orphan*/  nl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

int genl_family_add_grp(struct genl_family *family, uint32_t id,
			const char *name)
{
	struct genl_family_grp *grp;

	grp = calloc(1, sizeof(*grp));
	if (grp == NULL)
		return -NLE_NOMEM;

	grp->id = id;
	strncpy(grp->name, name, GENL_NAMSIZ - 1);

	nl_list_add_tail(&grp->list, &family->gf_mc_grps);

	return 0;
}