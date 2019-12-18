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
 int /*<<< orphan*/  DRIVER_CONFIG_NAME ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  IOV_CONFIG_NAME ; 
 int /*<<< orphan*/  PF_CONFIG_NAME ; 
 int /*<<< orphan*/  nvlist_move_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pci_iov_get_pf_subsystem_schema () ; 
 int /*<<< orphan*/ * pci_iov_schema_alloc_node () ; 

__attribute__((used)) static void
pci_iov_build_pf_schema(nvlist_t *schema, nvlist_t **driver_schema)
{
	nvlist_t *pf_schema, *iov_schema;

	pf_schema = pci_iov_schema_alloc_node();
	if (pf_schema == NULL) {
		nvlist_set_error(schema, ENOMEM);
		return;
	}

	iov_schema = pci_iov_get_pf_subsystem_schema();

	/*
	 * Note that if either *driver_schema or iov_schema is NULL, then
	 * nvlist_move_nvlist will put the schema in the error state and
	 * SR-IOV will fail to initialize later, so we don't have to explicitly
	 * handle that case.
	 */
	nvlist_move_nvlist(pf_schema, DRIVER_CONFIG_NAME, *driver_schema);
	nvlist_move_nvlist(pf_schema, IOV_CONFIG_NAME, iov_schema);
	nvlist_move_nvlist(schema, PF_CONFIG_NAME, pf_schema);
	*driver_schema = NULL;
}