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
struct xrefinfo {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIND_BY_XREF ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ xref_init_done ; 
 int /*<<< orphan*/  xrefinfo_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xrefinfo* xrefinfo_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
OF_device_register_xref(phandle_t xref, device_t dev)
{
	struct xrefinfo *xi;

	/*
	 * If the given xref handle doesn't already exist in the list then we
	 * add a list entry.  In theory this can only happen on a system where
	 * nodes don't contain phandle properties and xref and node handles are
	 * synonymous, so the xref handle is added as the node handle as well.
	 */
	if (xref_init_done) {
		if ((xi = xrefinfo_find(xref, FIND_BY_XREF)) == NULL)
			xrefinfo_add(xref, xref, dev);
		else 
			xi->dev = dev;
		return (0);
	}
	panic("Attempt to register device before xreflist_init");
}