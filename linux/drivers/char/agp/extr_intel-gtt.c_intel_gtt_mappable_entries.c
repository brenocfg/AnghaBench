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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  pcidev; int /*<<< orphan*/  bridge_dev; } ;

/* Variables and functions */
 int I810_GFX_MEM_WIN_32M ; 
 int I810_GFX_MEM_WIN_SIZE ; 
 int /*<<< orphan*/  I810_SMRAM_MISCC ; 
 int /*<<< orphan*/  I830_GMCH_CTRL ; 
 int I830_GMCH_MEM_64M ; 
 int I830_GMCH_MEM_MASK ; 
 int INTEL_GTT_GEN ; 
 unsigned int MB (int) ; 
 unsigned int PAGE_SHIFT ; 
 TYPE_1__ intel_private ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 unsigned int pci_resource_len (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int intel_gtt_mappable_entries(void)
{
	unsigned int aperture_size;

	if (INTEL_GTT_GEN == 1) {
		u32 smram_miscc;

		pci_read_config_dword(intel_private.bridge_dev,
				      I810_SMRAM_MISCC, &smram_miscc);

		if ((smram_miscc & I810_GFX_MEM_WIN_SIZE)
				== I810_GFX_MEM_WIN_32M)
			aperture_size = MB(32);
		else
			aperture_size = MB(64);
	} else if (INTEL_GTT_GEN == 2) {
		u16 gmch_ctrl;

		pci_read_config_word(intel_private.bridge_dev,
				     I830_GMCH_CTRL, &gmch_ctrl);

		if ((gmch_ctrl & I830_GMCH_MEM_MASK) == I830_GMCH_MEM_64M)
			aperture_size = MB(64);
		else
			aperture_size = MB(128);
	} else {
		/* 9xx supports large sizes, just look at the length */
		aperture_size = pci_resource_len(intel_private.pcidev, 2);
	}

	return aperture_size >> PAGE_SHIFT;
}