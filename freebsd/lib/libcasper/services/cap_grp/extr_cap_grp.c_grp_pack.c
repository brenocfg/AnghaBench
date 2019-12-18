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
typedef  int /*<<< orphan*/  uint64_t ;
struct group {char* gr_name; char* gr_passwd; char** gr_mem; scalar_t__ gr_gid; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  nvlname ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ grp_allowed_field (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  grp_allowed_group (int /*<<< orphan*/  const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static bool
grp_pack(const nvlist_t *limits, const struct group *grp, nvlist_t *nvl)
{
	char nvlname[64];
	int n;

	if (grp == NULL)
		return (true);

	/*
	 * If either name or GID is allowed, we allow it.
	 */
	if (!grp_allowed_group(limits, grp->gr_name, grp->gr_gid))
		return (false);

	if (grp_allowed_field(limits, "gr_name"))
		nvlist_add_string(nvl, "gr_name", grp->gr_name);
	else
		nvlist_add_string(nvl, "gr_name", "");
	if (grp_allowed_field(limits, "gr_passwd"))
		nvlist_add_string(nvl, "gr_passwd", grp->gr_passwd);
	else
		nvlist_add_string(nvl, "gr_passwd", "");
	if (grp_allowed_field(limits, "gr_gid"))
		nvlist_add_number(nvl, "gr_gid", (uint64_t)grp->gr_gid);
	else
		nvlist_add_number(nvl, "gr_gid", (uint64_t)-1);
	if (grp_allowed_field(limits, "gr_mem") && grp->gr_mem[0] != NULL) {
		unsigned int ngroups;

		for (ngroups = 0; grp->gr_mem[ngroups] != NULL; ngroups++) {
			n = snprintf(nvlname, sizeof(nvlname), "gr_mem[%u]",
			    ngroups);
			assert(n > 0 && n < (ssize_t)sizeof(nvlname));
			nvlist_add_string(nvl, nvlname, grp->gr_mem[ngroups]);
		}
		nvlist_add_number(nvl, "gr_nmem", (uint64_t)ngroups);
	}

	return (true);
}