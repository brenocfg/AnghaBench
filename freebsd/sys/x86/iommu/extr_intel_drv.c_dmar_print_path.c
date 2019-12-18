#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Device; int Function; } ;
typedef  TYPE_1__ ACPI_DMAR_PCI_PATH ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dmar_print_path(int busno, int depth, const ACPI_DMAR_PCI_PATH *path)
{
	int i;

	printf("[%d, ", busno);
	for (i = 0; i < depth; i++) {
		if (i != 0)
			printf(", ");
		printf("(%d, %d)", path[i].Device, path[i].Function);
	}
	printf("]");
}