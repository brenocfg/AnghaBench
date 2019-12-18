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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  devmap_add_entry (int const,int const) ; 

__attribute__((used)) static int
imx6_devmap_init(platform_t plat)
{
	const uint32_t IMX6_ARMMP_PHYS = 0x00a00000;
	const uint32_t IMX6_ARMMP_SIZE = 0x00100000;
	const uint32_t IMX6_AIPS1_PHYS = 0x02000000;
	const uint32_t IMX6_AIPS1_SIZE = 0x00100000;
	const uint32_t IMX6_AIPS2_PHYS = 0x02100000;
	const uint32_t IMX6_AIPS2_SIZE = 0x00100000;

	devmap_add_entry(IMX6_ARMMP_PHYS, IMX6_ARMMP_SIZE);
	devmap_add_entry(IMX6_AIPS1_PHYS, IMX6_AIPS1_SIZE);
	devmap_add_entry(IMX6_AIPS2_PHYS, IMX6_AIPS2_SIZE);

	return (0);
}