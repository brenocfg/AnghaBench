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
typedef  int u32 ;
struct drm_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int DRM_PCIE_SPEED_25 ; 
 int DRM_PCIE_SPEED_50 ; 
 int DRM_PCIE_SPEED_80 ; 
 int EINVAL ; 
 int PCIEM_LINK_CAP_MAX_SPEED ; 
 scalar_t__ PCIER_LINK_CAP ; 
 scalar_t__ PCIER_LINK_CAP2 ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int PCI_EXP_LNKCAP2_SLS_2_5GB ; 
 int PCI_EXP_LNKCAP2_SLS_5_0GB ; 
 int PCI_EXP_LNKCAP2_SLS_8_0GB ; 
 scalar_t__ PCI_VENDOR_ID_SERVERWORKS ; 
 scalar_t__ PCI_VENDOR_ID_VIA ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_pci_device_is_pcie (struct drm_device*) ; 
 int /*<<< orphan*/  pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

int drm_pcie_get_speed_cap_mask(struct drm_device *dev, u32 *mask)
{
	device_t root;
	int pos;
	u32 lnkcap = 0, lnkcap2 = 0;

	*mask = 0;
	if (!drm_pci_device_is_pcie(dev))
		return -EINVAL;

	root =
	    device_get_parent( /* pcib             */
	    device_get_parent( /* `-- pci          */
	    device_get_parent( /*     `-- vgapci   */
	    dev->dev)));       /*         `-- drmn */

	pos = 0;
	pci_find_cap(root, PCIY_EXPRESS, &pos);
	if (!pos)
		return -EINVAL;

	/* we've been informed via and serverworks don't make the cut */
	if (pci_get_vendor(root) == PCI_VENDOR_ID_VIA ||
	    pci_get_vendor(root) == PCI_VENDOR_ID_SERVERWORKS)
		return -EINVAL;

	lnkcap = pci_read_config(root, pos + PCIER_LINK_CAP, 4);
	lnkcap2 = pci_read_config(root, pos + PCIER_LINK_CAP2, 4);

	lnkcap &= PCIEM_LINK_CAP_MAX_SPEED;
	lnkcap2 &= 0xfe;

#define	PCI_EXP_LNKCAP2_SLS_2_5GB 0x02	/* Supported Link Speed 2.5GT/s */
#define	PCI_EXP_LNKCAP2_SLS_5_0GB 0x04	/* Supported Link Speed 5.0GT/s */
#define	PCI_EXP_LNKCAP2_SLS_8_0GB 0x08	/* Supported Link Speed 8.0GT/s */

	if (lnkcap2) { /* PCIE GEN 3.0 */
		if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_2_5GB)
			*mask |= DRM_PCIE_SPEED_25;
		if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_5_0GB)
			*mask |= DRM_PCIE_SPEED_50;
		if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_8_0GB)
			*mask |= DRM_PCIE_SPEED_80;
	} else {
		if (lnkcap & 1)
			*mask |= DRM_PCIE_SPEED_25;
		if (lnkcap & 2)
			*mask |= DRM_PCIE_SPEED_50;
	}

	DRM_INFO("probing gen 2 caps for device %x:%x = %x/%x\n", pci_get_vendor(root), pci_get_device(root), lnkcap, lnkcap2);
	return 0;
}