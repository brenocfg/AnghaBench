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
 int BCMA_DMP_RC_RESET ; 
 int /*<<< orphan*/  BCMA_DMP_RESETCTRL ; 
 int BHND_IOCTL_CLK_EN ; 
 int bhnd_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bhnd_read_ioctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool
bcma_is_hw_suspended(device_t dev, device_t child)
{
	uint32_t	rst;
	uint16_t	ioctl;
	int		error;

	/* Is core held in RESET? */
	error = bhnd_read_config(child, BCMA_DMP_RESETCTRL, &rst, 4);
	if (error) {
		device_printf(child, "error reading HW reset state: %d\n",
		    error);
		return (true);
	}

	if (rst & BCMA_DMP_RC_RESET)
		return (true);

	/* Is core clocked? */
	error = bhnd_read_ioctl(child, &ioctl);
	if (error) {
		device_printf(child, "error reading HW ioctl register: %d\n",
		    error);
		return (true);
	}

	if (!(ioctl & BHND_IOCTL_CLK_EN))
		return (true);

	return (false);
}