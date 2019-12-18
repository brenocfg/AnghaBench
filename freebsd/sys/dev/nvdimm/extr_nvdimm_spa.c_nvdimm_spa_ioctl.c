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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct thread {int dummy; } ;
struct nvdimm_spa_dev {int /*<<< orphan*/  spa_len; } ;
struct cdev {struct nvdimm_spa_dev* si_drv1; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_BSIZE ; 
#define  DIOCGMEDIASIZE 129 
#define  DIOCGSECTORSIZE 128 
 int ENOTTY ; 

__attribute__((used)) static int
nvdimm_spa_ioctl(struct cdev *cdev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	struct nvdimm_spa_dev *dev;
	int error;

	dev = cdev->si_drv1;
	error = 0;
	switch (cmd) {
	case DIOCGSECTORSIZE:
		*(u_int *)data = DEV_BSIZE;
		break;
	case DIOCGMEDIASIZE:
		*(off_t *)data = dev->spa_len;
		break;
	default:
		error = ENOTTY;
		break;
	}
	return (error);
}