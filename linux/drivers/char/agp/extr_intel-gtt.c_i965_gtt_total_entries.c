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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {TYPE_1__* pcidev; scalar_t__ registers; int /*<<< orphan*/  bridge_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  G4x_GMCH_SIZE_1M 138 
#define  G4x_GMCH_SIZE_2M 137 
 int G4x_GMCH_SIZE_MASK ; 
#define  G4x_GMCH_SIZE_VT_1M 136 
#define  G4x_GMCH_SIZE_VT_1_5M 135 
#define  G4x_GMCH_SIZE_VT_2M 134 
 scalar_t__ I810_PGETBL_CTL ; 
 int /*<<< orphan*/  I830_GMCH_CTRL ; 
#define  I965_PGETBL_SIZE_128KB 133 
#define  I965_PGETBL_SIZE_1MB 132 
#define  I965_PGETBL_SIZE_1_5MB 131 
#define  I965_PGETBL_SIZE_256KB 130 
#define  I965_PGETBL_SIZE_2MB 129 
#define  I965_PGETBL_SIZE_512KB 128 
 int I965_PGETBL_SIZE_MASK ; 
 int INTEL_GTT_GEN ; 
 int KB (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i965_adjust_pgetbl_size (int) ; 
 TYPE_2__ intel_private ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int i965_gtt_total_entries(void)
{
	int size;
	u32 pgetbl_ctl;
	u16 gmch_ctl;

	pci_read_config_word(intel_private.bridge_dev,
			     I830_GMCH_CTRL, &gmch_ctl);

	if (INTEL_GTT_GEN == 5) {
		switch (gmch_ctl & G4x_GMCH_SIZE_MASK) {
		case G4x_GMCH_SIZE_1M:
		case G4x_GMCH_SIZE_VT_1M:
			i965_adjust_pgetbl_size(I965_PGETBL_SIZE_1MB);
			break;
		case G4x_GMCH_SIZE_VT_1_5M:
			i965_adjust_pgetbl_size(I965_PGETBL_SIZE_1_5MB);
			break;
		case G4x_GMCH_SIZE_2M:
		case G4x_GMCH_SIZE_VT_2M:
			i965_adjust_pgetbl_size(I965_PGETBL_SIZE_2MB);
			break;
		}
	}

	pgetbl_ctl = readl(intel_private.registers+I810_PGETBL_CTL);

	switch (pgetbl_ctl & I965_PGETBL_SIZE_MASK) {
	case I965_PGETBL_SIZE_128KB:
		size = KB(128);
		break;
	case I965_PGETBL_SIZE_256KB:
		size = KB(256);
		break;
	case I965_PGETBL_SIZE_512KB:
		size = KB(512);
		break;
	/* GTT pagetable sizes bigger than 512KB are not possible on G33! */
	case I965_PGETBL_SIZE_1MB:
		size = KB(1024);
		break;
	case I965_PGETBL_SIZE_2MB:
		size = KB(2048);
		break;
	case I965_PGETBL_SIZE_1_5MB:
		size = KB(1024 + 512);
		break;
	default:
		dev_info(&intel_private.pcidev->dev,
			 "unknown page table size, assuming 512KB\n");
		size = KB(512);
	}

	return size/4;
}