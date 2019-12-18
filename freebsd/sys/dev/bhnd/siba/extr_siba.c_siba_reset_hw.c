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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct siba_devinfo {struct bhnd_resource** cfg_res; } ;
struct bhnd_resource {int dummy; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int BHND_IOCTL_CLK_EN ; 
 int BHND_IOCTL_CLK_FORCE ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  SIBA_CFG0_IMSTATE ; 
 int /*<<< orphan*/  SIBA_CFG0_TMSTATEHIGH ; 
 int /*<<< orphan*/  SIBA_CFG0_TMSTATELOW ; 
 int SIBA_IM_IBE ; 
 int SIBA_IM_TO ; 
 int SIBA_TMH_SERR ; 
 int SIBA_TML_RESET ; 
 int SIBA_TML_SICF_SHIFT ; 
 int UINT32_MAX ; 
 int bhnd_bus_read_4 (struct bhnd_resource*,int /*<<< orphan*/ ) ; 
 int bhnd_suspend_hw (scalar_t__,int) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  siba_write_target_state (scalar_t__,struct siba_devinfo*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
siba_reset_hw(device_t dev, device_t child, uint16_t ioctl,
    uint16_t reset_ioctl)
{
	struct siba_devinfo		*dinfo;
	struct bhnd_resource		*r;
	uint32_t			 ts_low, imstate;
	uint16_t			 clkflags;
	int				 error;

	if (device_get_parent(child) != dev)
		return (EINVAL);

	dinfo = device_get_ivars(child);

	/* Can't suspend the core without access to the CFG0 registers */
	if ((r = dinfo->cfg_res[0]) == NULL)
		return (ENODEV);

	/* We require exclusive control over BHND_IOCTL_CLK_(EN|FORCE) */
	clkflags = BHND_IOCTL_CLK_EN | BHND_IOCTL_CLK_FORCE;
	if (ioctl & clkflags)
		return (EINVAL);

	/* Place core into known RESET state */
	if ((error = bhnd_suspend_hw(child, reset_ioctl)))
		return (error);

	/* Set RESET, clear REJ, set the caller's IOCTL flags, and
	 * force clocks to ensure the signal propagates throughout the
	 * core. */
	ts_low = SIBA_TML_RESET |
		 (ioctl << SIBA_TML_SICF_SHIFT) |
		 (BHND_IOCTL_CLK_EN << SIBA_TML_SICF_SHIFT) |
		 (BHND_IOCTL_CLK_FORCE << SIBA_TML_SICF_SHIFT);

	siba_write_target_state(child, dinfo, SIBA_CFG0_TMSTATELOW,
	    ts_low, UINT32_MAX);

	/* Clear any target errors */
	if (bhnd_bus_read_4(r, SIBA_CFG0_TMSTATEHIGH) & SIBA_TMH_SERR) {
		siba_write_target_state(child, dinfo, SIBA_CFG0_TMSTATEHIGH,
		    0x0, SIBA_TMH_SERR);
	}

	/* Clear any initiator errors */
	imstate = bhnd_bus_read_4(r, SIBA_CFG0_IMSTATE);
	if (imstate & (SIBA_IM_IBE|SIBA_IM_TO)) {
		siba_write_target_state(child, dinfo, SIBA_CFG0_IMSTATE, 0x0,
		    SIBA_IM_IBE|SIBA_IM_TO);
	}

	/* Release from RESET while leaving clocks forced, ensuring the
	 * signal propagates throughout the core */
	siba_write_target_state(child, dinfo, SIBA_CFG0_TMSTATELOW, 0x0,
	    SIBA_TML_RESET);

	/* The core should now be active; we can clear the BHND_IOCTL_CLK_FORCE
	 * bit and allow the core to manage clock gating. */
	siba_write_target_state(child, dinfo, SIBA_CFG0_TMSTATELOW, 0x0,
	    (BHND_IOCTL_CLK_FORCE << SIBA_TML_SICF_SHIFT));

	return (0);
}