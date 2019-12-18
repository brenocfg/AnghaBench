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
struct driver_data {int slot_groups; TYPE_1__* pdev; int /*<<< orphan*/  product_type; scalar_t__ mmio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HOST_HSORG ; 
 int HSORG_HWREV ; 
 int HSORG_SLOTGROUPS ; 
 unsigned int MTIP_MAX_SLOT_GROUPS ; 
 int /*<<< orphan*/  MTIP_PRODUCT_ASICFPGA ; 
 int /*<<< orphan*/  MTIP_PRODUCT_UNKNOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void mtip_detect_product(struct driver_data *dd)
{
	u32 hwdata;
	unsigned int rev, slotgroups;

	/*
	 * HBA base + 0xFC [15:0] - vendor-specific hardware interface
	 * info register:
	 * [15:8] hardware/software interface rev#
	 * [   3] asic-style interface
	 * [ 2:0] number of slot groups, minus 1 (only valid for asic-style).
	 */
	hwdata = readl(dd->mmio + HOST_HSORG);

	dd->product_type = MTIP_PRODUCT_UNKNOWN;
	dd->slot_groups = 1;

	if (hwdata & 0x8) {
		dd->product_type = MTIP_PRODUCT_ASICFPGA;
		rev = (hwdata & HSORG_HWREV) >> 8;
		slotgroups = (hwdata & HSORG_SLOTGROUPS) + 1;
		dev_info(&dd->pdev->dev,
			"ASIC-FPGA design, HS rev 0x%x, "
			"%i slot groups [%i slots]\n",
			 rev,
			 slotgroups,
			 slotgroups * 32);

		if (slotgroups > MTIP_MAX_SLOT_GROUPS) {
			dev_warn(&dd->pdev->dev,
				"Warning: driver only supports "
				"%i slot groups.\n", MTIP_MAX_SLOT_GROUPS);
			slotgroups = MTIP_MAX_SLOT_GROUPS;
		}
		dd->slot_groups = slotgroups;
		return;
	}

	dev_warn(&dd->pdev->dev, "Unrecognized product id\n");
}