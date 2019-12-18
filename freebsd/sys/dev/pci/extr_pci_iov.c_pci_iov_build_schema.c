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
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_iov_build_pf_schema (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pci_iov_build_vf_schema (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * pci_iov_schema_alloc_node () ; 

__attribute__((used)) static nvlist_t *
pci_iov_build_schema(nvlist_t **pf, nvlist_t **vf)
{
	nvlist_t *schema, *pf_driver, *vf_driver;

	/* We always take ownership of the schemas. */
	pf_driver = *pf;
	*pf = NULL;
	vf_driver = *vf;
	*vf = NULL;

	schema = pci_iov_schema_alloc_node();
	if (schema == NULL)
		goto cleanup;

	pci_iov_build_pf_schema(schema, &pf_driver);
	pci_iov_build_vf_schema(schema, &vf_driver);

	if (nvlist_error(schema) != 0)
		goto cleanup;

	return (schema);

cleanup:
	nvlist_destroy(schema);
	nvlist_destroy(pf_driver);
	nvlist_destroy(vf_driver);
	return (NULL);
}