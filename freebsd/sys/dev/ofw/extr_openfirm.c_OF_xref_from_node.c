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
typedef  int /*<<< orphan*/  xref ;
struct xrefinfo {int /*<<< orphan*/  xref; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIND_BY_NODE ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ xref_init_done ; 
 struct xrefinfo* xrefinfo_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

phandle_t
OF_xref_from_node(phandle_t node)
{
	struct xrefinfo *xi;
	phandle_t xref;

	if (xref_init_done) {
		if ((xi = xrefinfo_find(node, FIND_BY_NODE)) == NULL)
			return (node);
		return (xi->xref);
	}

	if (OF_getencprop(node, "phandle", &xref, sizeof(xref)) == -1 &&
	    OF_getencprop(node, "ibm,phandle", &xref, sizeof(xref)) == -1 &&
	    OF_getencprop(node, "linux,phandle", &xref, sizeof(xref)) == -1)
		return (node);
	return (xref);
}