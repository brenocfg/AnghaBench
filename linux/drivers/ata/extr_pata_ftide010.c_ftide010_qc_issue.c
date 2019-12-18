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
struct ata_queued_cmd {struct ata_device* dev; struct ata_port* ap; } ;
struct ata_port {struct ata_device* private_data; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 unsigned int ata_bmdma_qc_issue (struct ata_queued_cmd*) ; 
 scalar_t__ ata_dma_enabled (struct ata_device*) ; 
 int /*<<< orphan*/  ftide010_set_dmamode (struct ata_port*,struct ata_device*) ; 

__attribute__((used)) static unsigned int ftide010_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *adev = qc->dev;

	/*
	 * If the device changed, i.e. slave->master, master->slave,
	 * then set up the DMA mode again so we are sure the timings
	 * are correct.
	 */
	if (adev != ap->private_data && ata_dma_enabled(adev))
		ftide010_set_dmamode(ap, adev);

	return ata_bmdma_qc_issue(qc);
}