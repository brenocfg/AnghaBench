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
struct pci_dev {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOSPC ; 
 int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int) ; 

__attribute__((used)) static int check_req(struct pci_dev *pdev, int nvec, char *prop_name)
{
	struct device_node *dn;
	const __be32 *p;
	u32 req_msi;

	dn = pci_device_to_OF_node(pdev);

	p = of_get_property(dn, prop_name, NULL);
	if (!p) {
		pr_debug("rtas_msi: No %s on %pOF\n", prop_name, dn);
		return -ENOENT;
	}

	req_msi = be32_to_cpup(p);
	if (req_msi < nvec) {
		pr_debug("rtas_msi: %s requests < %d MSIs\n", prop_name, nvec);

		if (req_msi == 0) /* Be paranoid */
			return -ENOSPC;

		return req_msi;
	}

	return 0;
}