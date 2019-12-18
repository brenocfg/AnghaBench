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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int CAP_SYSCTL_READ ; 
 int CAP_SYSCTL_WRITE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTCAPABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* calloc (int,size_t) ; 
 int errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int nametomib (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nvlist_exists_binary (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_exists_null (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_exists_number (int /*<<< orphan*/ *,char*) ; 
 void* nvlist_get_binary (int /*<<< orphan*/ *,char*,size_t*) ; 
 int nvlist_get_number (int /*<<< orphan*/ *,char*) ; 
 char* nvlist_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_move_binary (int /*<<< orphan*/ *,char*,void*,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int sysctl (int const*,size_t,void*,size_t*,void const*,size_t) ; 
 int /*<<< orphan*/  sysctl_allowed (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int sysctl_valid (int /*<<< orphan*/ *,int) ; 
 int sysctlbyname (char const*,void*,size_t*,void const*,size_t) ; 

__attribute__((used)) static int
sysctl_command(const char *cmd, const nvlist_t *limits, nvlist_t *nvlin,
    nvlist_t *nvlout)
{
	const char *name;
	const void *newp;
	const int *mibp;
	void *oldp;
	uint64_t operation;
	size_t oldlen, newlen, size;
	size_t *oldlenp;
	int error;

	if (strcmp(cmd, "sysctlnametomib") == 0)
		return (nametomib(limits, nvlin, nvlout));

	if (strcmp(cmd, "sysctlbyname") != 0 && strcmp(cmd, "sysctl") != 0)
		return (EINVAL);
	error = sysctl_valid(nvlin, false);
	if (error != 0)
		return (error);
	if (!sysctl_allowed(limits, nvlin))
		return (ENOTCAPABLE);

	operation = nvlist_get_number(nvlin, "operation");
	if ((operation & CAP_SYSCTL_WRITE) != 0) {
		if (!nvlist_exists_binary(nvlin, "newp"))
			return (EINVAL);
		newp = nvlist_get_binary(nvlin, "newp", &newlen);
		assert(newp != NULL && newlen > 0);
	} else {
		newp = NULL;
		newlen = 0;
	}

	if ((operation & CAP_SYSCTL_READ) != 0) {
		if (nvlist_exists_null(nvlin, "justsize")) {
			oldp = NULL;
			oldlen = 0;
			oldlenp = &oldlen;
		} else {
			if (!nvlist_exists_number(nvlin, "oldlen"))
				return (EINVAL);
			oldlen = (size_t)nvlist_get_number(nvlin, "oldlen");
			if (oldlen == 0)
				return (EINVAL);
			oldp = calloc(1, oldlen);
			if (oldp == NULL)
				return (ENOMEM);
			oldlenp = &oldlen;
		}
	} else {
		oldp = NULL;
		oldlen = 0;
		oldlenp = NULL;
	}

	if (strcmp(cmd, "sysctlbyname") == 0) {
		name = nvlist_get_string(nvlin, "name");
		error = sysctlbyname(name, oldp, oldlenp, newp, newlen);
	} else {
		mibp = nvlist_get_binary(nvlin, "mib", &size);
		error = sysctl(mibp, size / sizeof(*mibp), oldp, oldlenp, newp,
		    newlen);
	}
	if (error != 0) {
		error = errno;
		free(oldp);
		return (error);
	}

	if ((operation & CAP_SYSCTL_READ) != 0) {
		if (nvlist_exists_null(nvlin, "justsize"))
			nvlist_add_number(nvlout, "oldlen", (uint64_t)oldlen);
		else
			nvlist_move_binary(nvlout, "oldp", oldp, oldlen);
	}

	return (0);
}