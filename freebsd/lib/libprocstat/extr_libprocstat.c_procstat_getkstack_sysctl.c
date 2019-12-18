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
struct kinfo_kstack {int dummy; } ;
typedef  size_t pid_t ;

/* Variables and functions */
 int CTL_KERN ; 
 scalar_t__ ENOENT ; 
 scalar_t__ EPERM ; 
 scalar_t__ ESRCH ; 
 int KERN_PROC ; 
 int KERN_PROC_KSTACK ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct kinfo_kstack*) ; 
 struct kinfo_kstack* malloc (size_t) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int sysctl (int*,int /*<<< orphan*/ ,struct kinfo_kstack*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,size_t) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static struct kinfo_kstack *
procstat_getkstack_sysctl(pid_t pid, int *cntp)
{
	struct kinfo_kstack *kkstp;
	int error, name[4];
	size_t len;

	name[0] = CTL_KERN;
	name[1] = KERN_PROC;
	name[2] = KERN_PROC_KSTACK;
	name[3] = pid;

	len = 0;
	error = sysctl(name, nitems(name), NULL, &len, NULL, 0);
	if (error < 0 && errno != ESRCH && errno != EPERM && errno != ENOENT) {
		warn("sysctl: kern.proc.kstack: %d", pid);
		return (NULL);
	}
	if (error == -1 && errno == ENOENT) {
		warnx("sysctl: kern.proc.kstack unavailable"
		    " (options DDB or options STACK required in kernel)");
		return (NULL);
	}
	if (error == -1)
		return (NULL);
	kkstp = malloc(len);
	if (kkstp == NULL) {
		warn("malloc(%zu)", len);
		return (NULL);
	}
	if (sysctl(name, nitems(name), kkstp, &len, NULL, 0) == -1) {
		warn("sysctl: kern.proc.pid: %d", pid);
		free(kkstp);
		return (NULL);
	}
	*cntp = len / sizeof(*kkstp);

	return (kkstp);
}