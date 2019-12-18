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
struct mmc_ivars {scalar_t__ bus_width; int sec_count; int erase_sector; scalar_t__ read_only; int /*<<< orphan*/  quirks; int /*<<< orphan*/  timings; int /*<<< orphan*/  card_id_string; int /*<<< orphan*/  rca; } ;
typedef  enum mmc_bus_timing { ____Placeholder_mmc_bus_timing } mmc_bus_timing ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_QUIRKS_FMT ; 
 int bus_timing_max ; 
 int bus_timing_normal ; 
 scalar_t__ bus_width_1 ; 
 scalar_t__ bus_width_4 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ isset (int /*<<< orphan*/ *,int) ; 
 int mmc_timing_to_dtr (struct mmc_ivars*,int) ; 
 char* mmc_timing_to_string (int) ; 

__attribute__((used)) static void
mmc_log_card(device_t dev, struct mmc_ivars *ivar, int newcard)
{
	enum mmc_bus_timing timing;

	device_printf(dev, "Card at relative address 0x%04x%s:\n",
	    ivar->rca, newcard ? " added" : "");
	device_printf(dev, " card: %s\n", ivar->card_id_string);
	for (timing = bus_timing_max; timing > bus_timing_normal; timing--) {
		if (isset(&ivar->timings, timing))
			break;
	}
	device_printf(dev, " quirks: %b\n", ivar->quirks, MMC_QUIRKS_FMT);
	device_printf(dev, " bus: %ubit, %uMHz (%s timing)\n",
	    (ivar->bus_width == bus_width_1 ? 1 :
	    (ivar->bus_width == bus_width_4 ? 4 : 8)),
	    mmc_timing_to_dtr(ivar, timing) / 1000000,
	    mmc_timing_to_string(timing));
	device_printf(dev, " memory: %u blocks, erase sector %u blocks%s\n",
	    ivar->sec_count, ivar->erase_sector,
	    ivar->read_only ? ", read-only" : "");
}