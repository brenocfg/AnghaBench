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
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct nvd_disk {int /*<<< orphan*/  ns; } ;
struct disk {struct nvd_disk* d_drv1; } ;

/* Variables and functions */
 int nvme_ns_ioctl_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,struct thread*) ; 

__attribute__((used)) static int
nvd_ioctl(struct disk *dp, u_long cmd, void *data, int fflag,
    struct thread *td)
{
	struct nvd_disk		*ndisk = dp->d_drv1;

	return (nvme_ns_ioctl_process(ndisk->ns, cmd, data, fflag, td));
}