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
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIU2400_FLASH_ADDR ; 
 int /*<<< orphan*/  BIU2400_FLASH_DATA ; 
 int /*<<< orphan*/  ISP_DELAY (int) ; 
 unsigned int ISP_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_SWIZZLE_NVRAM_LONG (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  ISP_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ IS_25XX (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_26XX (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isp_rd_2400_nvram(ispsoftc_t *isp, uint32_t addr, uint32_t *rp)
{
	int loops = 0;
	uint32_t base = 0x7ffe0000;
	uint32_t tmp = 0;

	if (IS_26XX(isp)) {
		base = 0x7fe7c000;	/* XXX: Observation, may be wrong. */
	} else if (IS_25XX(isp)) {
		base = 0x7ff00000 | 0x48000;
	}
	ISP_WRITE(isp, BIU2400_FLASH_ADDR, base | addr);
	for (loops = 0; loops < 5000; loops++) {
		ISP_DELAY(10);
		tmp = ISP_READ(isp, BIU2400_FLASH_ADDR);
		if ((tmp & (1U << 31)) != 0) {
			break;
		}
	}
	if (tmp & (1U << 31)) {
		*rp = ISP_READ(isp, BIU2400_FLASH_DATA);
		ISP_SWIZZLE_NVRAM_LONG(isp, rp);
	} else {
		*rp = 0xffffffff;
	}
}