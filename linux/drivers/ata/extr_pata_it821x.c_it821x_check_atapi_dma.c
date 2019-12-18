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
struct it821x_dev {scalar_t__ timing10; scalar_t__ smart; } ;
struct ata_queued_cmd {struct ata_port* ap; } ;
struct ata_port {struct it821x_dev* private_data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ata_qc_raw_nbytes (struct ata_queued_cmd*) ; 

__attribute__((used)) static int it821x_check_atapi_dma(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct it821x_dev *itdev = ap->private_data;

	/* Only use dma for transfers to/from the media. */
	if (ata_qc_raw_nbytes(qc) < 2048)
		return -EOPNOTSUPP;

	/* No ATAPI DMA in smart mode */
	if (itdev->smart)
		return -EOPNOTSUPP;
	/* No ATAPI DMA on rev 10 */
	if (itdev->timing10)
		return -EOPNOTSUPP;
	/* Cool */
	return 0;
}