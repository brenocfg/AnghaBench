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
struct ep93xx_pata_data {int /*<<< orphan*/  t; } ;
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {struct ep93xx_pata_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFER_PIO_0 ; 
 int /*<<< orphan*/ * ata_timing_find_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xx_pata_port_start(struct ata_port *ap)
{
	struct ep93xx_pata_data *drv_data = ap->host->private_data;

	/*
	 * Set timings to safe values at startup (= number of ns from ATA
	 * specification), we'll switch to properly calculated values later.
	 */
	drv_data->t = *ata_timing_find_mode(XFER_PIO_0);
	return 0;
}