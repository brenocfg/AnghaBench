#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sriov_initialized; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_1__ qlnx_host_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IOV_SCHEMA_HASDEFAULT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int pci_iov_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_iov_schema_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iov_schema_add_uint16 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_iov_schema_add_unicast_mac (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pci_iov_schema_alloc_node () ; 

__attribute__((used)) static void
qlnx_initialize_sriov(qlnx_host_t *ha)
{
	device_t	dev;
	nvlist_t	*pf_schema, *vf_schema;
	int		iov_error;

	dev = ha->pci_dev;

	pf_schema = pci_iov_schema_alloc_node();
	vf_schema = pci_iov_schema_alloc_node();

	pci_iov_schema_add_unicast_mac(vf_schema, "mac-addr", 0, NULL);
	pci_iov_schema_add_bool(vf_schema, "allow-set-mac",
		IOV_SCHEMA_HASDEFAULT, FALSE);
	pci_iov_schema_add_bool(vf_schema, "allow-promisc",
		IOV_SCHEMA_HASDEFAULT, FALSE);
	pci_iov_schema_add_uint16(vf_schema, "num-queues",
		IOV_SCHEMA_HASDEFAULT, 1);

	iov_error = pci_iov_attach(dev, pf_schema, vf_schema);

	if (iov_error != 0) {
		ha->sriov_initialized = 0;
	} else {
		device_printf(dev, "SRIOV initialized\n");
		ha->sriov_initialized = 1;
	}
			
	return;
}