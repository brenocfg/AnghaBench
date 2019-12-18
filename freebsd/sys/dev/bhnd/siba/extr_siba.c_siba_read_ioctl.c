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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIBA_CFG0_TMSTATELOW ; 
 int /*<<< orphan*/  SIBA_REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TML_SICF ; 
 int bhnd_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
siba_read_ioctl(device_t dev, device_t child, uint16_t *ioctl)
{
	uint32_t	ts_low;
	int		error;

	if ((error = bhnd_read_config(child, SIBA_CFG0_TMSTATELOW, &ts_low, 4)))
		return (error);

	*ioctl = (SIBA_REG_GET(ts_low, TML_SICF));
	return (0);
}