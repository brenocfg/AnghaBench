#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct via_isa_bridge {scalar_t__ id; } ;
struct ata_host {struct via_isa_bridge* private_data; } ;
struct ata_device {scalar_t__ class; int /*<<< orphan*/  id; TYPE_2__* link; } ;
typedef  int /*<<< orphan*/  model_num ;
struct TYPE_4__ {TYPE_1__* ap; } ;
struct TYPE_3__ {struct ata_host* host; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATAPI ; 
 int /*<<< orphan*/  ATA_ID_PROD ; 
 int /*<<< orphan*/  ATA_ID_PROD_LEN ; 
 unsigned long ATA_MASK_PIO ; 
 unsigned long ATA_MASK_UDMA ; 
 scalar_t__ PCI_DEVICE_ID_VIA_82C586_0 ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*) ; 
 int /*<<< orphan*/  ata_id_c_string (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_atapi_dma_dmi_table ; 
 scalar_t__ strcmp (unsigned char*,char*) ; 

__attribute__((used)) static unsigned long via_mode_filter(struct ata_device *dev, unsigned long mask)
{
	struct ata_host *host = dev->link->ap->host;
	const struct via_isa_bridge *config = host->private_data;
	unsigned char model_num[ATA_ID_PROD_LEN + 1];

	if (config->id == PCI_DEVICE_ID_VIA_82C586_0) {
		ata_id_c_string(dev->id, model_num, ATA_ID_PROD, sizeof(model_num));
		if (strcmp(model_num, "TS64GSSD25-M") == 0) {
			ata_dev_warn(dev,
	"disabling UDMA mode due to reported lockups with this device\n");
			mask &= ~ ATA_MASK_UDMA;
		}
	}

	if (dev->class == ATA_DEV_ATAPI &&
	    dmi_check_system(no_atapi_dma_dmi_table)) {
		ata_dev_warn(dev, "controller locks up on ATAPI DMA, forcing PIO\n");
		mask &= ATA_MASK_PIO;
	}

	return mask;
}