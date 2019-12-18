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
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 struct passwd* getpwnam (char const*) ; 
 int /*<<< orphan*/  nvlist_exists_string (int /*<<< orphan*/  const*,char*) ; 
 char* nvlist_get_string (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  pwd_pack (int /*<<< orphan*/  const*,struct passwd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pwd_getpwnam(const nvlist_t *limits, const nvlist_t *nvlin, nvlist_t *nvlout)
{
	struct passwd *pwd;
	const char *name;

	if (!nvlist_exists_string(nvlin, "name"))
		return (EINVAL);
	name = nvlist_get_string(nvlin, "name");
	assert(name != NULL);

	errno = 0;
	pwd = getpwnam(name);
	if (errno != 0)
		return (errno);

	(void)pwd_pack(limits, pwd, nvlout);

	return (0);
}