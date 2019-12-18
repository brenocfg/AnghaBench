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
typedef  scalar_t__ uint16_t ;
struct nicpf {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IOV_SCHEMA_HASDEFAULT ; 
 scalar_t__ PCIR_SRIOV_TOTAL_VFS ; 
 int /*<<< orphan*/  PCIZ_SRIOV ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int pci_find_extcap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_iov_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_iov_schema_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iov_schema_add_unicast_mac (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pci_iov_schema_alloc_node () ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int nic_sriov_init(device_t dev, struct nicpf *nic)
{
#ifdef PCI_IOV
	nvlist_t *pf_schema, *vf_schema;
	int iov_pos;
	int err;
	uint16_t total_vf_cnt;

	err = pci_find_extcap(dev, PCIZ_SRIOV, &iov_pos);
	if (err != 0) {
		device_printf(dev,
		    "SR-IOV capability is not found in PCIe config space\n");
		return (err);
	}
	/* Fix-up the number of enabled VFs */
	total_vf_cnt = pci_read_config(dev, iov_pos + PCIR_SRIOV_TOTAL_VFS, 2);
	if (total_vf_cnt == 0)
		return (ENXIO);

	/* Attach SR-IOV */
	pf_schema = pci_iov_schema_alloc_node();
	vf_schema = pci_iov_schema_alloc_node();
	pci_iov_schema_add_unicast_mac(vf_schema, "mac-addr", 0, NULL);
	/*
	 * All VFs can change their MACs.
	 * This flag will be ignored but we set it just for the record.
	 */
	pci_iov_schema_add_bool(vf_schema, "allow-set-mac",
	    IOV_SCHEMA_HASDEFAULT, TRUE);

	err = pci_iov_attach(dev, pf_schema, vf_schema);
	if (err != 0) {
		device_printf(dev,
		    "Failed to initialize SR-IOV (error=%d)\n",
		    err);
		return (err);
	}
#endif
	return (0);
}