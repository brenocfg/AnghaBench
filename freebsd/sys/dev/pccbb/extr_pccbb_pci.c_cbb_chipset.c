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
typedef  scalar_t__ uint32_t ;
struct yenta_chipinfo {scalar_t__ yc_id; char* yc_name; int yc_chiptype; } ;

/* Variables and functions */
 struct yenta_chipinfo* yc_chipsets ; 

__attribute__((used)) static int
cbb_chipset(uint32_t pci_id, const char **namep)
{
	struct yenta_chipinfo *ycp;

	for (ycp = yc_chipsets; ycp->yc_id != 0 && pci_id != ycp->yc_id; ++ycp)
		continue;
	if (namep != NULL)
		*namep = ycp->yc_name;
	return (ycp->yc_chiptype);
}