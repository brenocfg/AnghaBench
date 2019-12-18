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
typedef  int /*<<< orphan*/  u_long ;
struct uuid {int dummy; } ;
struct efi_cfgtbl {int /*<<< orphan*/  ct_data; int /*<<< orphan*/  ct_uuid; } ;
struct TYPE_2__ {int /*<<< orphan*/  st_entries; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  bcmp (int /*<<< orphan*/ *,struct uuid*,int) ; 
 struct efi_cfgtbl* efi_cfgtbl ; 
 scalar_t__ efi_phys_to_kva (int /*<<< orphan*/ ) ; 
 TYPE_1__* efi_systbl ; 

int
efi_get_table(struct uuid *uuid, void **ptr)
{
	struct efi_cfgtbl *ct;
	u_long count;

	if (efi_cfgtbl == NULL || efi_systbl == NULL)
		return (ENXIO);
	count = efi_systbl->st_entries;
	ct = efi_cfgtbl;
	while (count--) {
		if (!bcmp(&ct->ct_uuid, uuid, sizeof(*uuid))) {
			*ptr = (void *)efi_phys_to_kva(ct->ct_data);
			return (0);
		}
		ct++;
	}
	return (ENOENT);
}