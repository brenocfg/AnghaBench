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
struct nvme_namespace {int /*<<< orphan*/  cdev; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int nvme_ns_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct thread*) ; 

int
nvme_ns_ioctl_process(struct nvme_namespace *ns, u_long cmd, caddr_t arg,
    int flag, struct thread *td)
{
	return (nvme_ns_ioctl(ns->cdev, cmd, arg, flag, td));
}