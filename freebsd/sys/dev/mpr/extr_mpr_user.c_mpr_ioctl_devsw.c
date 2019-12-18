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
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ SV_CURPROC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 int mpr_ioctl (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct thread*) ; 
 int mpr_ioctl32 (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct thread*) ; 

__attribute__((used)) static int
mpr_ioctl_devsw(struct cdev *dev, u_long com, caddr_t arg, int flag,
    struct thread *td)
{
#ifdef COMPAT_FREEBSD32
	if (SV_CURPROC_FLAG(SV_ILP32))
		return (mpr_ioctl32(dev, com, arg, flag, td));
#endif
	return (mpr_ioctl(dev, com, arg, flag, td));
}