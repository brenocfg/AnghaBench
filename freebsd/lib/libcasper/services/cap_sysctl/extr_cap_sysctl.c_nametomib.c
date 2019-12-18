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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTCAPABLE ; 
 int errno ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (size_t) ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char*,int*,size_t) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 char* nvlist_get_string (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  sysctl_allowed (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int sysctlnametomib (char const*,int*,size_t*) ; 

__attribute__((used)) static int
nametomib(const nvlist_t *limits, const nvlist_t *nvlin, nvlist_t *nvlout)
{
	const char *name;
	size_t size;
	int error, *mibp;

	if (!sysctl_allowed(limits, nvlin))
		return (ENOTCAPABLE);

	name = nvlist_get_string(nvlin, "name");
	size = (size_t)nvlist_get_number(nvlin, "size");

	mibp = malloc(size * sizeof(*mibp));
	if (mibp == NULL)
		return (ENOMEM);

	error = sysctlnametomib(name, mibp, &size);
	if (error != 0) {
		error = errno;
		free(mibp);
		return (error);
	}

	nvlist_add_binary(nvlout, "mib", mibp, size * sizeof(*mibp));

	return (0);
}