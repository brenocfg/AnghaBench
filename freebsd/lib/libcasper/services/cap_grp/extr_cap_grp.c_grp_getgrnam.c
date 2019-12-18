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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 struct group* getgrnam (char const*) ; 
 int /*<<< orphan*/  grp_pack (int /*<<< orphan*/  const*,struct group*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists_string (int /*<<< orphan*/  const*,char*) ; 
 char* nvlist_get_string (int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static int
grp_getgrnam(const nvlist_t *limits, const nvlist_t *nvlin, nvlist_t *nvlout)
{
	struct group *grp;
	const char *name;

	if (!nvlist_exists_string(nvlin, "name"))
		return (EINVAL);
	name = nvlist_get_string(nvlin, "name");
	assert(name != NULL);

	errno = 0;
	grp = getgrnam(name);
	if (errno != 0)
		return (errno);

	(void)grp_pack(limits, grp, nvlout);

	return (0);
}