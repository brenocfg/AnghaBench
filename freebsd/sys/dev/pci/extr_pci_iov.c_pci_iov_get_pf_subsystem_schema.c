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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOV_SCHEMA_REQUIRED ; 
 int /*<<< orphan*/  pci_iov_schema_add_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_iov_schema_add_uint16 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pci_iov_schema_alloc_node () ; 

__attribute__((used)) static nvlist_t *
pci_iov_get_pf_subsystem_schema(void)
{
	nvlist_t *pf;

	pf = pci_iov_schema_alloc_node();
	if (pf == NULL)
		return (NULL);

	pci_iov_schema_add_uint16(pf, "num_vfs", IOV_SCHEMA_REQUIRED, -1);
	pci_iov_schema_add_string(pf, "device", IOV_SCHEMA_REQUIRED, NULL);

	return (pf);
}