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
struct ofw_bus_iinfo {int dummy; } ;
struct isa_regs {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  ofw_pci_intr_t ;
typedef  int /*<<< orphan*/  ofw_isa_intr_t ;
typedef  int /*<<< orphan*/  mintr ;
typedef  int /*<<< orphan*/  intr ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIB_ROUTE_INTERRUPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_lookup_imap (int /*<<< orphan*/ ,struct ofw_bus_iinfo*,struct isa_regs*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

ofw_pci_intr_t
ofw_isa_route_intr(device_t bridge, phandle_t node, struct ofw_bus_iinfo *ii,
    ofw_isa_intr_t intr)
{
	struct isa_regs reg;
	device_t pbridge;
	ofw_isa_intr_t mintr;

	pbridge = device_get_parent(device_get_parent(bridge));
	/*
	 * If we get a match from using the map, the resulting INO is
	 * fully specified, so we may not continue to map.
	 */
	if (!ofw_bus_lookup_imap(node, ii, &reg, sizeof(reg),
	    &intr, sizeof(intr), &mintr, sizeof(mintr), NULL)) {
		/* Try routing at the parent bridge. */
		mintr = PCIB_ROUTE_INTERRUPT(pbridge, bridge, intr);
	}
	return (mintr);
}