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
struct kinfo_proc {int /*<<< orphan*/  ki_pid; int /*<<< orphan*/ * ki_fd; } ;
struct filedesc {unsigned short fd_cmask; } ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_all (int /*<<< orphan*/ *,unsigned long,struct filedesc*,int) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
procstat_getumask_kvm(kvm_t *kd, struct kinfo_proc *kp, unsigned short *maskp)
{
	struct filedesc fd;

	assert(kd != NULL);
	assert(kp != NULL);
	if (kp->ki_fd == NULL)
		return (-1);
	if (!kvm_read_all(kd, (unsigned long)kp->ki_fd, &fd, sizeof(fd))) {
		warnx("can't read filedesc at %p for pid %d", kp->ki_fd,
		    kp->ki_pid);
		return (-1);
	}
	*maskp = fd.fd_cmask;
	return (0);
}