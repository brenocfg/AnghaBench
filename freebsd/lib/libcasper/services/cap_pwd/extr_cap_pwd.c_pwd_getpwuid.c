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
typedef  scalar_t__ uid_t ;
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ errno ; 
 struct passwd* getpwuid (scalar_t__) ; 
 int /*<<< orphan*/  nvlist_exists_number (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  pwd_pack (int /*<<< orphan*/  const*,struct passwd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pwd_getpwuid(const nvlist_t *limits, const nvlist_t *nvlin, nvlist_t *nvlout)
{
	struct passwd *pwd;
	uid_t uid;

	if (!nvlist_exists_number(nvlin, "uid"))
		return (EINVAL);

	uid = (uid_t)nvlist_get_number(nvlin, "uid");

	errno = 0;
	pwd = getpwuid(uid);
	if (errno != 0)
		return (errno);

	(void)pwd_pack(limits, pwd, nvlout);

	return (0);
}