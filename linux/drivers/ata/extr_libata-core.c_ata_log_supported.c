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
typedef  int u8 ;
struct ata_port {int /*<<< orphan*/ * sector_buf; } ;
struct ata_device {TYPE_1__* link; } ;
struct TYPE_2__ {struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_LOG_DIRECTORY ; 
 scalar_t__ ata_read_log_page (struct ata_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ata_log_supported(struct ata_device *dev, u8 log)
{
	struct ata_port *ap = dev->link->ap;

	if (ata_read_log_page(dev, ATA_LOG_DIRECTORY, 0, ap->sector_buf, 1))
		return false;
	return get_unaligned_le16(&ap->sector_buf[log * 2]) ? true : false;
}