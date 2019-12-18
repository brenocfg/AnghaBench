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
struct group {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ errno ; 
 struct group* getgrgid (scalar_t__) ; 
 int /*<<< orphan*/  grp_pack (int /*<<< orphan*/  const*,struct group*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists_number (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static int
grp_getgrgid(const nvlist_t *limits, const nvlist_t *nvlin, nvlist_t *nvlout)
{
	struct group *grp;
	gid_t gid;

	if (!nvlist_exists_number(nvlin, "gid"))
		return (EINVAL);

	gid = (gid_t)nvlist_get_number(nvlin, "gid");

	errno = 0;
	grp = getgrgid(gid);
	if (errno != 0)
		return (errno);

	(void)grp_pack(limits, grp, nvlout);

	return (0);
}