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
struct kinfo_proc {int ki_structsize; int ki_pid; } ;
typedef  int pid_t ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_PROC ; 
 int KERN_PROC_PID ; 
 int /*<<< orphan*/  free (struct kinfo_proc*) ; 
 struct kinfo_proc* malloc (size_t) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 scalar_t__ sysctl (int*,int /*<<< orphan*/ ,struct kinfo_proc*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct kinfo_proc *
kinfo_getproc(pid_t pid)
{
	struct kinfo_proc *kipp;
	int mib[4];
	size_t len;

	len = 0;
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PID;
	mib[3] = pid;
	if (sysctl(mib, nitems(mib), NULL, &len, NULL, 0) < 0)
		return (NULL);

	kipp = malloc(len);
	if (kipp == NULL)
		return (NULL);

	if (sysctl(mib, nitems(mib), kipp, &len, NULL, 0) < 0)
		goto bad;
	if (len != sizeof(*kipp))
		goto bad;
	if (kipp->ki_structsize != sizeof(*kipp))
		goto bad;
	if (kipp->ki_pid != pid)
		goto bad;
	return (kipp);
bad:
	free(kipp);
	return (NULL);
}