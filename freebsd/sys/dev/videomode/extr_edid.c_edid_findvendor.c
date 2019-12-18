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
struct TYPE_2__ {char const* name; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int edid_nvendors ; 
 TYPE_1__* edid_vendors ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static const char *
edid_findvendor(const char *vendor)
{
#ifdef	EDIDVERBOSE
	int	n;

	for (n = 0; n < edid_nvendors; n++)
		if (memcmp(edid_vendors[n].vendor, vendor, 3) == 0)
			return edid_vendors[n].name;
#endif
	return NULL;
}