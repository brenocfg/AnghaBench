#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ product; char const* name; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int edid_nproducts ; 
 TYPE_1__* edid_products ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static const char *
edid_findproduct(const char *vendor, uint16_t product)
{
#ifdef	EDIDVERBOSE
	int	n;

	for (n = 0; n < edid_nproducts; n++)
		if (edid_products[n].product == product &&
		    memcmp(edid_products[n].vendor, vendor, 3) == 0)
			return edid_products[n].name;
#endif	/* EDIDVERBOSE */
	return NULL;

}