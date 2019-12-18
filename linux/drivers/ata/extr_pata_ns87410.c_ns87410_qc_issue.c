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
struct ata_device {scalar_t__ pio_mode; } ;

/* Variables and functions */
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ns87410_set_piomode (struct ata_port*,struct ata_device*) ; 

__attribute__((used)) static unsigned int ns87410_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *adev = qc->dev;

	/* If modes have been configured and the channel data is not loaded
	   then load it. We have to check if pio_mode is set as the core code
	   does not set adev->pio_mode to XFER_PIO_0 while probing as would be
	   logical */

	if (adev->pio_mode && adev != ap->private_data)
		ns87410_set_piomode(ap, adev);

	return ata_sff_qc_issue(qc);
}