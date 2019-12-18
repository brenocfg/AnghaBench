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
 int BHND_IOCTL_CLK_EN ; 
 int BHND_IOCTL_CLK_FORCE ; 
 int EINVAL ; 
 int ENODEV ; 
 int UINT16_MAX ; 
 int bcma_dmp_write_reset (scalar_t__,struct bcma_devinfo*,int) ; 
 int bhnd_suspend_hw (scalar_t__,int) ; 
 int bhnd_write_ioctl (scalar_t__,int,int) ; 
 struct bcma_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 

__attribute__((used)) static int
bcma_reset_hw(device_t dev, device_t child, uint16_t ioctl,
    uint16_t reset_ioctl)
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

	/* Place core into known RESET state */
	if ((error = bhnd_suspend_hw(child, reset_ioctl)))
		return (error);

	/*
	 * Leaving the core in reset:
	 * - Set the caller's IOCTL flags
	 * - Enable clocks
	 * - Force clock distribution to ensure propagation throughout the
	 *   core.
	 */
	if ((error = bhnd_write_ioctl(child, ioctl | clkflags, UINT16_MAX)))
		return (error);

	/* Bring the core out of reset */
	if ((error = bcma_dmp_write_reset(child, dinfo, 0x0)))
		return (error);

	/* Disable forced clock gating (leaving clock enabled) */
	error = bhnd_write_ioctl(child, 0x0, BHND_IOCTL_CLK_FORCE);
	if (error)
		return (error);

	return (0);
}