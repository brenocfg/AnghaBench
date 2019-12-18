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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int RESET_ASSERT ; 
 int /*<<< orphan*/  SYSCTL_RSTCTRL ; 
 int /*<<< orphan*/  mtk_sysctl_clr_set (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int
mtk_reset_set(device_t dev, int index, int value)
{
	uint32_t mask;

	/* index 0 is SoC reset, indices 1 - 31 are valid peripheral resets */
	if (index < 1 || index > 31)
		return (EINVAL);

	mask = (1u << index);

	if (value == RESET_ASSERT)
		mtk_sysctl_clr_set(SYSCTL_RSTCTRL, 0, mask);
	else
		mtk_sysctl_clr_set(SYSCTL_RSTCTRL, mask, 0);

	return (0);
}