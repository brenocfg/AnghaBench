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
typedef  int uint16_t ;
struct bhnd_resource {int dummy; } ;
struct bcma_devinfo {struct bhnd_resource* res_agent; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_DMP_RC_RESET ; 
 int BHND_IOCTL_CLK_EN ; 
 int BHND_IOCTL_CLK_FORCE ; 
 int EINVAL ; 
 int ENODEV ; 
 int bcma_dmp_wait_reset (scalar_t__,struct bcma_devinfo*) ; 
 int bcma_dmp_write_reset (scalar_t__,struct bcma_devinfo*,int /*<<< orphan*/ ) ; 
 int bhnd_write_ioctl (scalar_t__,int,int) ; 
 struct bcma_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 

__attribute__((used)) static int
bcma_suspend_hw(device_t dev, device_t child, uint16_t ioctl)
{
	struct bcma_devinfo	*dinfo;
	struct bhnd_resource	*r;
	uint16_t		 clkflags;
	int			 error;

	if (device_get_parent(child) != dev)
		return (EINVAL);

	dinfo = device_get_ivars(child);

	/* We require exclusive control over BHND_IOCTL_CLK_(EN|FORCE) */
	clkflags = BHND_IOCTL_CLK_EN | BHND_IOCTL_CLK_FORCE;
	if (ioctl & clkflags)
		return (EINVAL);

	/* Can't suspend the core without access to the agent registers */
	if ((r = dinfo->res_agent) == NULL)
		return (ENODEV);

	/* Wait for any pending reset operations to clear */
	if ((error = bcma_dmp_wait_reset(child, dinfo)))
		return (error);

	/* Put core into reset (if not already in reset) */
	if ((error = bcma_dmp_write_reset(child, dinfo, BCMA_DMP_RC_RESET)))
		return (error);

	/* Write core flags (and clear CLK_EN/CLK_FORCE) */
	if ((error = bhnd_write_ioctl(child, ioctl, ~clkflags)))
		return (error);

	return (0);
}