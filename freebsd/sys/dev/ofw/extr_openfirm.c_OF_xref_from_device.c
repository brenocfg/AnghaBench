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
struct xrefinfo {int /*<<< orphan*/  xref; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIND_BY_DEV ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ xref_init_done ; 
 struct xrefinfo* xrefinfo_find (uintptr_t,int /*<<< orphan*/ ) ; 

phandle_t
OF_xref_from_device(device_t dev)
{
	struct xrefinfo *xi;

	if (xref_init_done) {
		if ((xi = xrefinfo_find((uintptr_t)dev, FIND_BY_DEV)) == NULL)
			return (0);
		return (xi->xref);
	}
	panic("Attempt to find xref before xreflist_init");
}