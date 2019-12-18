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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  efi_guid_tbl_compile () ; 
 int efi_guid_to_str (int /*<<< orphan*/ *,char**) ; 
 TYPE_1__* guid_tbl ; 
 size_t nitems (TYPE_1__*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
efi_guid_to_name(efi_guid_t *guid, char **name)
{
	size_t i;
	uint32_t status;

	efi_guid_tbl_compile();
	for (i = 0; i < nitems(guid_tbl); i++) {
		if (uuid_equal(guid, &guid_tbl[i].guid, &status)) {
			*name = strdup(guid_tbl[i].name);
			return (0);
		}
	}
	return (efi_guid_to_str(guid, name));
}