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
struct xrefinfo {int node; } ;
typedef  int phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIND_BY_XREF ; 
 int OF_child_xref_phandle (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OF_peer (int /*<<< orphan*/ ) ; 
 scalar_t__ xref_init_done ; 
 struct xrefinfo* xrefinfo_find (int,int /*<<< orphan*/ ) ; 

phandle_t
OF_node_from_xref(phandle_t xref)
{
	struct xrefinfo *xi;
	phandle_t node;

	if (xref_init_done) {
		if ((xi = xrefinfo_find(xref, FIND_BY_XREF)) == NULL)
			return (xref);
		return (xi->node);
	}

	if ((node = OF_child_xref_phandle(OF_peer(0), xref)) == -1)
		return (xref);
	return (node);
}