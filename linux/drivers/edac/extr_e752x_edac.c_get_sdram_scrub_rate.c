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
typedef  int u16 ;
struct scrubrate {scalar_t__ bandwidth; int scrubval; } ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {scalar_t__ pvt_info; } ;
struct e752x_pvt {TYPE_1__* dev_info; struct pci_dev* dev_d0f0; } ;
struct TYPE_2__ {scalar_t__ ctl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  E752X_MCHSCRB ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_3100_0 ; 
 scalar_t__ SDRATE_EOT ; 
 int /*<<< orphan*/  e752x_printk (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 struct scrubrate* scrubrates_e752x ; 
 struct scrubrate* scrubrates_i3100 ; 

__attribute__((used)) static int get_sdram_scrub_rate(struct mem_ctl_info *mci)
{
	const struct scrubrate *scrubrates;
	struct e752x_pvt *pvt = (struct e752x_pvt *) mci->pvt_info;
	struct pci_dev *pdev = pvt->dev_d0f0;
	u16 scrubval;
	int i;

	if (pvt->dev_info->ctl_dev == PCI_DEVICE_ID_INTEL_3100_0)
		scrubrates = scrubrates_i3100;
	else
		scrubrates = scrubrates_e752x;

	/* Find the bandwidth matching the memory scrubber configuration */
	pci_read_config_word(pdev, E752X_MCHSCRB, &scrubval);
	scrubval = scrubval & 0x0f;

	for (i = 0; scrubrates[i].bandwidth != SDRATE_EOT; i++)
		if (scrubrates[i].scrubval == scrubval)
			break;

	if (scrubrates[i].bandwidth == SDRATE_EOT) {
		e752x_printk(KERN_WARNING,
			"Invalid sdram scrub control value: 0x%x\n", scrubval);
		return -1;
	}
	return scrubrates[i].bandwidth;

}