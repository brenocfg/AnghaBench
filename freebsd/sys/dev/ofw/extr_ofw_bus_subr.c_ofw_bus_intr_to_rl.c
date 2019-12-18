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
typedef  int uint32_t ;
struct resource_list {int dummy; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  icells ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int ENOENT ; 
 int ERANGE ; 
 int /*<<< orphan*/  M_OFWPROP ; 
 int OF_getencprop_alloc_multi (scalar_t__,char*,int,void**) ; 
 int /*<<< orphan*/  OF_node_from_xref (scalar_t__) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 int OF_searchencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 scalar_t__ OF_xref_from_node (scalar_t__) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_find_iparent (scalar_t__) ; 
 int ofw_bus_map_intr (int /*<<< orphan*/ ,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  resource_list_add (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

int
ofw_bus_intr_to_rl(device_t dev, phandle_t node,
    struct resource_list *rl, int *rlen)
{
	phandle_t iparent;
	uint32_t icells, *intr;
	int err, i, irqnum, nintr, rid;
	boolean_t extended;

	nintr = OF_getencprop_alloc_multi(node, "interrupts",  sizeof(*intr),
	    (void **)&intr);
	if (nintr > 0) {
		iparent = ofw_bus_find_iparent(node);
		if (iparent == 0) {
			device_printf(dev, "No interrupt-parent found, "
			    "assuming direct parent\n");
			iparent = OF_parent(node);
			iparent = OF_xref_from_node(iparent);
		}
		if (OF_searchencprop(OF_node_from_xref(iparent), 
		    "#interrupt-cells", &icells, sizeof(icells)) == -1) {
			device_printf(dev, "Missing #interrupt-cells "
			    "property, assuming <1>\n");
			icells = 1;
		}
		if (icells < 1 || icells > nintr) {
			device_printf(dev, "Invalid #interrupt-cells property "
			    "value <%d>, assuming <1>\n", icells);
			icells = 1;
		}
		extended = false;
	} else {
		nintr = OF_getencprop_alloc_multi(node, "interrupts-extended",
		    sizeof(*intr), (void **)&intr);
		if (nintr <= 0)
			return (0);
		extended = true;
	}
	err = 0;
	rid = 0;
	for (i = 0; i < nintr; i += icells) {
		if (extended) {
			iparent = intr[i++];
			if (OF_searchencprop(OF_node_from_xref(iparent), 
			    "#interrupt-cells", &icells, sizeof(icells)) == -1) {
				device_printf(dev, "Missing #interrupt-cells "
				    "property\n");
				err = ENOENT;
				break;
			}
			if (icells < 1 || (i + icells) > nintr) {
				device_printf(dev, "Invalid #interrupt-cells "
				    "property value <%d>\n", icells);
				err = ERANGE;
				break;
			}
		}
		irqnum = ofw_bus_map_intr(dev, iparent, icells, &intr[i]);
		resource_list_add(rl, SYS_RES_IRQ, rid++, irqnum, irqnum, 1);
	}
	if (rlen != NULL)
		*rlen = rid;
	free(intr, M_OFWPROP);
	return (err);
}