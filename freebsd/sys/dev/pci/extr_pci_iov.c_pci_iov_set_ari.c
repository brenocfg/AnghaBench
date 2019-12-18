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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  PCIB_ARI_ENABLED (int /*<<< orphan*/ ) ; 
 int PCIM_SRIOV_ARI_EN ; 
 scalar_t__ PCIR_SRIOV_CTL ; 
 int /*<<< orphan*/  PCIZ_SRIOV ; 
 int device_get_children (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_extcap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int pci_get_function (int /*<<< orphan*/ *) ; 
 int pci_read_config (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ *,scalar_t__,int,int) ; 

__attribute__((used)) static int
pci_iov_set_ari(device_t bus)
{
	device_t lowest;
	device_t *devlist;
	int i, error, devcount, lowest_func, lowest_pos, iov_pos, dev_func;
	uint16_t iov_ctl;

	/* If ARI is disabled on the downstream port there is nothing to do. */
	if (!PCIB_ARI_ENABLED(device_get_parent(bus)))
		return (0);

	error = device_get_children(bus, &devlist, &devcount);

	if (error != 0)
		return (error);

	lowest = NULL;
	for (i = 0; i < devcount; i++) {
		if (pci_find_extcap(devlist[i], PCIZ_SRIOV, &iov_pos) == 0) {
			dev_func = pci_get_function(devlist[i]);
			if (lowest == NULL || dev_func < lowest_func) {
				lowest = devlist[i];
				lowest_func = dev_func;
				lowest_pos = iov_pos;
			}
		}
	}
	free(devlist, M_TEMP);

	/*
	 * If we called this function some device must have the SR-IOV
	 * capability.
	 */
	KASSERT(lowest != NULL,
	    ("Could not find child of %s with SR-IOV capability",
	    device_get_nameunit(bus)));

	iov_ctl = pci_read_config(lowest, lowest_pos + PCIR_SRIOV_CTL, 2);
	iov_ctl |= PCIM_SRIOV_ARI_EN;
	pci_write_config(lowest, lowest_pos + PCIR_SRIOV_CTL, iov_ctl, 2);
	if ((pci_read_config(lowest, lowest_pos + PCIR_SRIOV_CTL, 2) &
	    PCIM_SRIOV_ARI_EN) == 0) {
		device_printf(lowest, "failed to enable ARI\n");
		return (ENXIO);
	}
	return (0);
}