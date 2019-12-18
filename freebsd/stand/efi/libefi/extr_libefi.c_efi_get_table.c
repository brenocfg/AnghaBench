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
struct TYPE_4__ {int NumberOfTableEntries; TYPE_1__* ConfigurationTable; } ;
struct TYPE_3__ {void* VendorTable; int /*<<< orphan*/  VendorGuid; } ;
typedef  int /*<<< orphan*/  EFI_GUID ;

/* Variables and functions */
 TYPE_2__* ST ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void *
efi_get_table(EFI_GUID *tbl)
{
	EFI_GUID *id;
	int i;

	for (i = 0; i < ST->NumberOfTableEntries; i++) {
		id = &ST->ConfigurationTable[i].VendorGuid;
		if (!memcmp(id, tbl, sizeof(EFI_GUID)))
			return (ST->ConfigurationTable[i].VendorTable);
	}
	return (NULL);
}