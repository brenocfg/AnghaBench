#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Length; int EnumerationId; int Bus; int /*<<< orphan*/  EntryType; } ;
struct TYPE_3__ {int Device; int /*<<< orphan*/  Function; } ;
typedef  TYPE_1__ ACPI_DMAR_PCI_PATH ;
typedef  TYPE_2__ ACPI_DMAR_DEVICE_SCOPE ;

/* Variables and functions */
 char* devscope_type2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
acpi_handle_dmar_devscope(void *addr, int remaining)
{
	char sep;
	int pathlen;
	ACPI_DMAR_PCI_PATH *path, *pathend;
	ACPI_DMAR_DEVICE_SCOPE *devscope = addr;

	if (remaining < (int)sizeof(ACPI_DMAR_DEVICE_SCOPE))
		return (-1);

	if (remaining < devscope->Length)
		return (-1);

	printf("\n");
	printf("\t\tType=%s\n", devscope_type2str(devscope->EntryType));
	printf("\t\tLength=%d\n", devscope->Length);
	printf("\t\tEnumerationId=%d\n", devscope->EnumerationId);
	printf("\t\tStartBusNumber=%d\n", devscope->Bus);

	path = (ACPI_DMAR_PCI_PATH *)(devscope + 1);
	pathlen = devscope->Length - sizeof(ACPI_DMAR_DEVICE_SCOPE);
	pathend = path + pathlen / sizeof(ACPI_DMAR_PCI_PATH);
	if (path < pathend) {
		sep = '{';
		printf("\t\tPath=");
		do {
			printf("%c%d:%d", sep, path->Device, path->Function);
			sep=',';
			path++;
		} while (path < pathend);
		printf("}\n");
	}

	return (devscope->Length);
}