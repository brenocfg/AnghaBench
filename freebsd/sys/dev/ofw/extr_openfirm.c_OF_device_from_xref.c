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
struct xrefinfo {int /*<<< orphan*/ * dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIND_BY_XREF ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ xref_init_done ; 
 struct xrefinfo* xrefinfo_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

device_t
OF_device_from_xref(phandle_t xref)
{
	struct xrefinfo *xi;

	if (xref_init_done) {
		if ((xi = xrefinfo_find(xref, FIND_BY_XREF)) == NULL)
			return (NULL);
		return (xi->dev);
	}
	panic("Attempt to find device before xreflist_init");
}