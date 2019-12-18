#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bcma_device {int dummy; } ;
struct TYPE_2__ {struct bcma_device* core; } ;
struct bcma_bus {TYPE_1__ drv_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_OTPL ; 
 int BCMA_CC_OTPL_GURGN_OFFSET ; 
 int /*<<< orphan*/  BCMA_CC_OTPS ; 
 int BCMA_CC_OTPS_GU_PROG_HW ; 
 int BCMA_CC_SPROM ; 
 int bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcma_sprom_onchip_offset(struct bcma_bus *bus)
{
	struct bcma_device *cc = bus->drv_cc.core;
	u32 offset;

	/* verify OTP status */
	if ((bcma_read32(cc, BCMA_CC_OTPS) & BCMA_CC_OTPS_GU_PROG_HW) == 0)
		return 0;

	/* obtain bit offset from otplayout register */
	offset = (bcma_read32(cc, BCMA_CC_OTPL) & BCMA_CC_OTPL_GURGN_OFFSET);
	return BCMA_CC_SPROM + (offset >> 3);
}