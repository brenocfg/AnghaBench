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
typedef  size_t pid_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_PROC ; 
 int KERN_PROC_GROUPS ; 
 int /*<<< orphan*/  _SC_NGROUPS_MAX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int sysctl (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,size_t) ; 

__attribute__((used)) static gid_t *
procstat_getgroups_sysctl(pid_t pid, unsigned int *cntp)
{
	int mib[4];
	size_t len;
	gid_t *groups;

	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_GROUPS;
	mib[3] = pid;
	len = (sysconf(_SC_NGROUPS_MAX) + 1) * sizeof(gid_t);
	groups = malloc(len);
	if (groups == NULL) {
		warn("malloc(%zu)", len);
		return (NULL);
	}
	if (sysctl(mib, nitems(mib), groups, &len, NULL, 0) == -1) {
		warn("sysctl: kern.proc.groups: %d", pid);
		free(groups);
		return (NULL);
	}
	*cntp = len / sizeof(gid_t);
	return (groups);
}