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
struct fwmem_softc {int /*<<< orphan*/  eui; } ;
struct fw_eui64 {int dummy; } ;
struct cdev {struct fwmem_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  fw_proc ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int EINVAL ; 
#define  FW_GDEUI64 129 
#define  FW_SDEUI64 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
fwmem_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flag, fw_proc *td)
{
	struct fwmem_softc *fms;
	int err = 0;

	fms = dev->si_drv1;
	switch (cmd) {
	case FW_SDEUI64:
		bcopy(data, &fms->eui, sizeof(struct fw_eui64));
		break;
	case FW_GDEUI64:
		bcopy(&fms->eui, data, sizeof(struct fw_eui64));
		break;
	default:
		err = EINVAL;
	}
	return (err);
}