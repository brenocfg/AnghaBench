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
struct fdt_clock_info {scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FDT_CIFLAG_RUNNING ; 
 int /*<<< orphan*/  SYSCTL_CLKCFG1 ; 
 int mtk_sysctl_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_clock_get_info(device_t dev, int index, struct fdt_clock_info *info)
{
	uint32_t mask;

	if (index < 0 || index > 31 || info == NULL)
		return (EINVAL);

	if (mtk_sysctl_get(SYSCTL_CLKCFG1) & mask)
		info->flags = FDT_CIFLAG_RUNNING;
	else
		info->flags = 0;

	return (0);
}