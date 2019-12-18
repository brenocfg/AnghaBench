#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cdrom_device_info {unsigned long capacity; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* select_disc ) (struct cdrom_device_info*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_SELECT_DISC ; 
 int /*<<< orphan*/  CDROM_CAN (int /*<<< orphan*/ ) ; 
 unsigned long CDSL_CURRENT ; 
 unsigned long CDSL_NONE ; 
 int /*<<< orphan*/  CD_CHANGER ; 
 int /*<<< orphan*/  CD_DO_IOCTL ; 
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  cd_dbg (int /*<<< orphan*/ ,char*) ; 
 int cdrom_select_disc (struct cdrom_device_info*,unsigned long) ; 
 int stub1 (struct cdrom_device_info*,unsigned long) ; 

__attribute__((used)) static int cdrom_ioctl_select_disc(struct cdrom_device_info *cdi,
		unsigned long arg)
{
	cd_dbg(CD_DO_IOCTL, "entering CDROM_SELECT_DISC\n");

	if (!CDROM_CAN(CDC_SELECT_DISC))
		return -ENOSYS;

	if (arg != CDSL_CURRENT && arg != CDSL_NONE) {
		if (arg >= cdi->capacity)
			return -EINVAL;
	}

	/*
	 * ->select_disc is a hook to allow a driver-specific way of
	 * seleting disc.  However, since there is no equivalent hook for
	 * cdrom_slot_status this may not actually be useful...
	 */
	if (cdi->ops->select_disc)
		return cdi->ops->select_disc(cdi, arg);

	cd_dbg(CD_CHANGER, "Using generic cdrom_select_disc()\n");
	return cdrom_select_disc(cdi, arg);
}