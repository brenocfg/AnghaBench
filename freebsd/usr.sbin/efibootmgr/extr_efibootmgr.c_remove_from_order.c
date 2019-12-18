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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_GLOBAL_GUID ; 
 scalar_t__ efi_get_variable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ le16dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ set_bootvar (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__) ; 

__attribute__((used)) static void
remove_from_order(uint16_t bootnum)
{
	uint32_t attrs;
	size_t size, i, j;
	uint8_t *new, *data;

	if (efi_get_variable(EFI_GLOBAL_GUID, "BootOrder", &data, &size, &attrs) < 0)
		return;

	new = malloc(size);
	if (new == NULL)
		err(1, "malloc");

	for (j = i = 0; i < size; i += sizeof(uint16_t)) {
		if (le16dec(data + i) == bootnum)
			continue;
		memcpy(new + j, data + i, sizeof(uint16_t));
		j += sizeof(uint16_t);
	}
	if (i == j)
		warnx("Boot variable %04x not in BootOrder", bootnum);
	else if (set_bootvar("BootOrder", new, j) < 0)
		err(1, "Unable to update BootOrder with new value");
	free(new);
}