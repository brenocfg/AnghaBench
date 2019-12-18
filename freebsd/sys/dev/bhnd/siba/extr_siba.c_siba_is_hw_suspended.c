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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BHND_IOCTL_CLK_EN ; 
 int /*<<< orphan*/  SIBA_CFG0_TMSTATELOW ; 
 int SIBA_REG_GET (int,int /*<<< orphan*/ ) ; 
 int SIBA_TML_REJ_MASK ; 
 int SIBA_TML_RESET ; 
 int /*<<< orphan*/  TML_SICF ; 
 int bhnd_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool
siba_is_hw_suspended(device_t dev, device_t child)
{
	uint32_t		ts_low;
	uint16_t		ioctl;
	int			error;

	/* Fetch target state */
	error = bhnd_read_config(child, SIBA_CFG0_TMSTATELOW, &ts_low, 4);
	if (error) {
		device_printf(child, "error reading HW reset state: %d\n",
		    error);
		return (true);
	}

	/* Is core held in RESET? */
	if (ts_low & SIBA_TML_RESET)
		return (true);

	/* Is target reject enabled? */
	if (ts_low & SIBA_TML_REJ_MASK)
		return (true);

	/* Is core clocked? */
	ioctl = SIBA_REG_GET(ts_low, TML_SICF);
	if (!(ioctl & BHND_IOCTL_CLK_EN))
		return (true);

	return (false);
}