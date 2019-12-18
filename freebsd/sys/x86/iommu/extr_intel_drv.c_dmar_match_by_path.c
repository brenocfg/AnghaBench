#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dmar_unit {int /*<<< orphan*/  unit; } ;
struct TYPE_8__ {int /*<<< orphan*/  Length; } ;
struct TYPE_6__ {int Length; } ;
struct TYPE_7__ {int Segment; int Flags; TYPE_1__ Header; } ;
typedef  int /*<<< orphan*/  ACPI_DMAR_PCI_PATH ;
typedef  TYPE_2__ ACPI_DMAR_HARDWARE_UNIT ;
typedef  TYPE_3__ ACPI_DMAR_DEVICE_SCOPE ;

/* Variables and functions */
 int ACPI_DMAR_INCLUDE_ALL ; 
 TYPE_2__* dmar_find_by_index (int /*<<< orphan*/ ) ; 
 int dmar_match_devscope (TYPE_3__*,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool
dmar_match_by_path(struct dmar_unit *unit, int dev_domain, int dev_busno,
    const ACPI_DMAR_PCI_PATH *dev_path, int dev_path_len, const char **banner)
{
	ACPI_DMAR_HARDWARE_UNIT *dmarh;
	ACPI_DMAR_DEVICE_SCOPE *devscope;
	char *ptr, *ptrend;
	int match;

	dmarh = dmar_find_by_index(unit->unit);
	if (dmarh == NULL)
		return (false);
	if (dmarh->Segment != dev_domain)
		return (false);
	if ((dmarh->Flags & ACPI_DMAR_INCLUDE_ALL) != 0) {
		if (banner != NULL)
			*banner = "INCLUDE_ALL";
		return (true);
	}
	ptr = (char *)dmarh + sizeof(*dmarh);
	ptrend = (char *)dmarh + dmarh->Header.Length;
	while (ptr < ptrend) {
		devscope = (ACPI_DMAR_DEVICE_SCOPE *)ptr;
		ptr += devscope->Length;
		match = dmar_match_devscope(devscope, dev_busno, dev_path,
		    dev_path_len);
		if (match == -1)
			return (false);
		if (match == 1) {
			if (banner != NULL)
				*banner = "specific match";
			return (true);
		}
	}
	return (false);
}