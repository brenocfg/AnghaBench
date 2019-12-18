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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_APERTURE_BAR ; 
 int /*<<< orphan*/  AMD64_GARTAPERTUREBASE ; 
 int /*<<< orphan*/  AMD64_GARTAPERTURECTL ; 
 scalar_t__ agp_aperture_valid (int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  gart_set_size_and_enable (struct pci_dev*,int) ; 
 int hweight16 (int) ; 
 int pci_bus_address (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fix_northbridge(struct pci_dev *nb, struct pci_dev *agp, u16 cap)
{
	u64 aper, nb_aper;
	int order = 0;
	u32 nb_order, nb_base;
	u16 apsize;

	pci_read_config_dword(nb, AMD64_GARTAPERTURECTL, &nb_order);
	nb_order = (nb_order >> 1) & 7;
	pci_read_config_dword(nb, AMD64_GARTAPERTUREBASE, &nb_base);
	nb_aper = (u64)nb_base << 25;

	/* Northbridge seems to contain crap. Try the AGP bridge. */

	pci_read_config_word(agp, cap+0x14, &apsize);
	if (apsize == 0xffff) {
		if (agp_aperture_valid(nb_aper, (32*1024*1024)<<nb_order))
			return 0;
		return -1;
	}

	apsize &= 0xfff;
	/* Some BIOS use weird encodings not in the AGPv3 table. */
	if (apsize & 0xff)
		apsize |= 0xf00;
	order = 7 - hweight16(apsize);

	aper = pci_bus_address(agp, AGP_APERTURE_BAR);

	/*
	 * On some sick chips APSIZE is 0. This means it wants 4G
	 * so let double check that order, and lets trust the AMD NB settings
	 */
	if (order >=0 && aper + (32ULL<<(20 + order)) > 0x100000000ULL) {
		dev_info(&agp->dev, "aperture size %u MB is not right, using settings from NB\n",
			 32 << order);
		order = nb_order;
	}

	if (nb_order >= order) {
		if (agp_aperture_valid(nb_aper, (32*1024*1024)<<nb_order))
			return 0;
	}

	dev_info(&agp->dev, "aperture from AGP @ %Lx size %u MB\n",
		 aper, 32 << order);
	if (order < 0 || !agp_aperture_valid(aper, (32*1024*1024)<<order))
		return -1;

	gart_set_size_and_enable(nb, order);
	pci_write_config_dword(nb, AMD64_GARTAPERTUREBASE, aper >> 25);

	return 0;
}