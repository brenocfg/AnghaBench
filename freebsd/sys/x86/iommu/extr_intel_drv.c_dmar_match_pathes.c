#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum AcpiDmarScopeType { ____Placeholder_AcpiDmarScopeType } AcpiDmarScopeType ;
struct TYPE_4__ {scalar_t__ Device; scalar_t__ Function; } ;
typedef  TYPE_1__ ACPI_DMAR_PCI_PATH ;

/* Variables and functions */
 int ACPI_DMAR_SCOPE_TYPE_ENDPOINT ; 

__attribute__((used)) static int
dmar_match_pathes(int busno1, const ACPI_DMAR_PCI_PATH *path1, int depth1,
    int busno2, const ACPI_DMAR_PCI_PATH *path2, int depth2,
    enum AcpiDmarScopeType scope_type)
{
	int i, depth;

	if (busno1 != busno2)
		return (0);
	if (scope_type == ACPI_DMAR_SCOPE_TYPE_ENDPOINT && depth1 != depth2)
		return (0);
	depth = depth1;
	if (depth2 < depth)
		depth = depth2;
	for (i = 0; i < depth; i++) {
		if (path1[i].Device != path2[i].Device ||
		    path1[i].Function != path2[i].Function)
			return (0);
	}
	return (1);
}