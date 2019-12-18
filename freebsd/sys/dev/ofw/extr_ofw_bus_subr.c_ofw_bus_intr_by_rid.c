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
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  icells ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int ENOENT ; 
 int ERANGE ; 
 int ESRCH ; 
 int /*<<< orphan*/  M_OFWPROP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int OF_getencprop_alloc_multi (scalar_t__,char*,int,void**) ; 
 int /*<<< orphan*/  OF_node_from_xref (scalar_t__) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 int OF_searchencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 scalar_t__ OF_xref_from_node (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ ofw_bus_find_iparent (scalar_t__) ; 

int
ofw_bus_intr_by_rid(device_t dev, phandle_t node, int wanted_rid,
    phandle_t *producer, int *ncells, pcell_t **cells)
{
	phandle_t iparent;
	uint32_t icells, *intr;
	int err, i, nintr, rid;
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
			return (ESRCH);
		extended = true;
	}
	err = ESRCH;
	rid = 0;
	for (i = 0; i < nintr; i += icells, rid++) {
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
		if (rid == wanted_rid) {
			*cells = malloc(icells * sizeof(**cells), M_OFWPROP,
			    M_WAITOK);
			*producer = iparent;
			*ncells= icells;
			memcpy(*cells, intr + i, icells * sizeof(**cells));
			err = 0;
			break;
		}
	}
	free(intr, M_OFWPROP);
	return (err);
}