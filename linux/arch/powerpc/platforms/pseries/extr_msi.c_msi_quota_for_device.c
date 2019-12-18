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
struct pci_dev {int dummy; } ;
struct msi_counts {int num_devices; int quota; int request; int spare; int over_quota; int /*<<< orphan*/  requestor; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  count_non_bridge_devices ; 
 int /*<<< orphan*/  count_spare_msis ; 
 struct device_node* find_pe_dn (struct pci_dev*,int*) ; 
 struct device_node* find_pe_total_msi (struct pci_dev*,int*) ; 
 int /*<<< orphan*/  memset (struct msi_counts*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_traverse_device_nodes (struct device_node*,int /*<<< orphan*/ ,struct msi_counts*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msi_quota_for_device(struct pci_dev *dev, int request)
{
	struct device_node *pe_dn;
	struct msi_counts counts;
	int total;

	pr_debug("rtas_msi: calc quota for %s, request %d\n", pci_name(dev),
		  request);

	pe_dn = find_pe_total_msi(dev, &total);
	if (!pe_dn)
		pe_dn = find_pe_dn(dev, &total);

	if (!pe_dn) {
		pr_err("rtas_msi: couldn't find PE for %s\n", pci_name(dev));
		goto out;
	}

	pr_debug("rtas_msi: found PE %pOF\n", pe_dn);

	memset(&counts, 0, sizeof(struct msi_counts));

	/* Work out how many devices we have below this PE */
	pci_traverse_device_nodes(pe_dn, count_non_bridge_devices, &counts);

	if (counts.num_devices == 0) {
		pr_err("rtas_msi: found 0 devices under PE for %s\n",
			pci_name(dev));
		goto out;
	}

	counts.quota = total / counts.num_devices;
	if (request <= counts.quota)
		goto out;

	/* else, we have some more calculating to do */
	counts.requestor = pci_device_to_OF_node(dev);
	counts.request = request;
	pci_traverse_device_nodes(pe_dn, count_spare_msis, &counts);

	/* If the quota isn't an integer multiple of the total, we can
	 * use the remainder as spare MSIs for anyone that wants them. */
	counts.spare += total % counts.num_devices;

	/* Divide any spare by the number of over-quota requestors */
	if (counts.over_quota)
		counts.quota += counts.spare / counts.over_quota;

	/* And finally clamp the request to the possibly adjusted quota */
	request = min(counts.quota, request);

	pr_debug("rtas_msi: request clamped to quota %d\n", request);
out:
	of_node_put(pe_dn);

	return request;
}