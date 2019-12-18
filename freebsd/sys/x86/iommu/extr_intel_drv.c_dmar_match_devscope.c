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
struct TYPE_3__ {int Length; int /*<<< orphan*/  EntryType; int /*<<< orphan*/  Bus; } ;
typedef  int /*<<< orphan*/  ACPI_DMAR_PCI_PATH ;
typedef  TYPE_1__ ACPI_DMAR_DEVICE_SCOPE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DMAR_SCOPE_TYPE_BRIDGE ; 
 int /*<<< orphan*/  ACPI_DMAR_SCOPE_TYPE_ENDPOINT ; 
 int dmar_match_pathes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
dmar_match_devscope(ACPI_DMAR_DEVICE_SCOPE *devscope, int dev_busno,
    const ACPI_DMAR_PCI_PATH *dev_path, int dev_path_len)
{
	ACPI_DMAR_PCI_PATH *path;
	int path_len;

	if (devscope->Length < sizeof(*devscope)) {
		printf("dmar_match_devscope: corrupted DMAR table, dl %d\n",
		    devscope->Length);
		return (-1);
	}
	if (devscope->EntryType != ACPI_DMAR_SCOPE_TYPE_ENDPOINT &&
	    devscope->EntryType != ACPI_DMAR_SCOPE_TYPE_BRIDGE)
		return (0);
	path_len = devscope->Length - sizeof(*devscope);
	if (path_len % 2 != 0) {
		printf("dmar_match_devscope: corrupted DMAR table, dl %d\n",
		    devscope->Length);
		return (-1);
	}
	path_len /= 2;
	path = (ACPI_DMAR_PCI_PATH *)(devscope + 1);
	if (path_len == 0) {
		printf("dmar_match_devscope: corrupted DMAR table, dl %d\n",
		    devscope->Length);
		return (-1);
	}

	return (dmar_match_pathes(devscope->Bus, path, path_len, dev_busno,
	    dev_path, dev_path_len, devscope->EntryType));
}