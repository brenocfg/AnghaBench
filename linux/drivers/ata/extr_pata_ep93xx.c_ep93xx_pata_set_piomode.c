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
struct ata_timing {int dummy; } ;
struct ep93xx_pata_data {int /*<<< orphan*/  ide_base; int /*<<< orphan*/  iordy; struct ata_timing t; } ;
struct ata_port {TYPE_1__* host; } ;
struct ata_device {scalar_t__ pio_mode; } ;
struct TYPE_2__ {struct ep93xx_pata_data* private_data; } ;

/* Variables and functions */
 int ATA_TIMING_8BIT ; 
 int ATA_TIMING_SETUP ; 
 scalar_t__ XFER_PIO_0 ; 
 struct ata_device* ata_dev_pair (struct ata_device*) ; 
 int /*<<< orphan*/  ata_pio_need_iordy (struct ata_device*) ; 
 int /*<<< orphan*/  ata_timing_compute (struct ata_device*,scalar_t__,struct ata_timing*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_timing_merge (struct ata_timing*,struct ata_timing*,struct ata_timing*,int) ; 
 int /*<<< orphan*/  ep93xx_pata_enable_pio (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ep93xx_pata_set_piomode(struct ata_port *ap,
				    struct ata_device *adev)
{
	struct ep93xx_pata_data *drv_data = ap->host->private_data;
	struct ata_device *pair = ata_dev_pair(adev);
	/*
	 * Calculate timings for the delay loop, assuming ep93xx cpu speed
	 * is 200MHz (maximum possible for ep93xx). If actual cpu speed is
	 * slower, we will wait a bit longer in each delay.
	 * Additional division of cpu speed by 5, because single iteration
	 * of our delay loop takes 5 cpu cycles (25ns).
	 */
	unsigned long T = 1000000 / (200 / 5);

	ata_timing_compute(adev, adev->pio_mode, &drv_data->t, T, 0);
	if (pair && pair->pio_mode) {
		struct ata_timing t;
		ata_timing_compute(pair, pair->pio_mode, &t, T, 0);
		ata_timing_merge(&t, &drv_data->t, &drv_data->t,
			ATA_TIMING_SETUP | ATA_TIMING_8BIT);
	}
	drv_data->iordy = ata_pio_need_iordy(adev);

	ep93xx_pata_enable_pio(drv_data->ide_base,
			       adev->pio_mode - XFER_PIO_0);
}