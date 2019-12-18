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
struct group {int /*<<< orphan*/  gr_mem; scalar_t__ gr_gid; int /*<<< orphan*/  gr_passwd; int /*<<< orphan*/  gr_name; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  explicit_bzero (struct group*,int) ; 
 int group_unpack_members (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char**,size_t*) ; 
 int group_unpack_string (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *,char**,size_t*) ; 
 int /*<<< orphan*/  nvlist_exists_string (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static int
group_unpack(const nvlist_t *nvl, struct group *grp, char *buffer,
    size_t bufsize)
{
	int error;

	if (!nvlist_exists_string(nvl, "gr_name"))
		return (EINVAL);

	explicit_bzero(grp, sizeof(*grp));

	error = group_unpack_string(nvl, "gr_name", &grp->gr_name, &buffer,
	    &bufsize);
	if (error != 0)
		return (error);
	error = group_unpack_string(nvl, "gr_passwd", &grp->gr_passwd, &buffer,
	    &bufsize);
	if (error != 0)
		return (error);
	grp->gr_gid = (gid_t)nvlist_get_number(nvl, "gr_gid");
	error = group_unpack_members(nvl, &grp->gr_mem, &buffer, &bufsize);
	if (error != 0)
		return (error);

	return (0);
}