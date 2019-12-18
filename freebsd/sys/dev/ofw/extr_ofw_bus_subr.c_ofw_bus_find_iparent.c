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
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  iparent ;

/* Variables and functions */
 scalar_t__ OF_hasprop (scalar_t__,char*) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 int OF_searchencprop (scalar_t__,char*,scalar_t__*,int) ; 
 scalar_t__ OF_xref_from_node (scalar_t__) ; 

phandle_t
ofw_bus_find_iparent(phandle_t node)
{
	phandle_t iparent;

	if (OF_searchencprop(node, "interrupt-parent", &iparent,
		    sizeof(iparent)) == -1) {
		for (iparent = node; iparent != 0;
		    iparent = OF_parent(iparent)) {
			if (OF_hasprop(iparent, "interrupt-controller"))
				break;
		}
		iparent = OF_xref_from_node(iparent);
	}
	return (iparent);
}