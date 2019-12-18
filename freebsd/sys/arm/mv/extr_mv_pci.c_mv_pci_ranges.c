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
struct mv_pci_range {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  debugf (char*,...) ; 
 int /*<<< orphan*/  mv_pci_range_dump (struct mv_pci_range*) ; 
 int mv_pci_ranges_decode (int /*<<< orphan*/ ,struct mv_pci_range*,struct mv_pci_range*) ; 

__attribute__((used)) static int
mv_pci_ranges(phandle_t node, struct mv_pci_range *io_space,
    struct mv_pci_range *mem_space)
{
	int err;

	debugf("Processing PCI node: %x\n", node);
	if ((err = mv_pci_ranges_decode(node, io_space, mem_space)) != 0) {
		debugf("could not decode parent PCI node 'ranges'\n");
		return (err);
	}

	debugf("Post fixup dump:\n");
	mv_pci_range_dump(io_space);
	mv_pci_range_dump(mem_space);
	return (0);
}