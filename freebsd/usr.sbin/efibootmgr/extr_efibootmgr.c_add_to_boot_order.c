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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_GLOBAL_GUID ; 
 scalar_t__ ENOENT ; 
 scalar_t__ efi_get_variable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ set_bootvar (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
add_to_boot_order(char *bootvar)
{
	size_t size;
	uint32_t attrs;
	uint16_t val;
	uint8_t *data, *new;

	val = strtoul(&bootvar[4], NULL, 16);

	if (efi_get_variable(EFI_GLOBAL_GUID, "BootOrder", &data, &size, &attrs) < 0) {
		if (errno == ENOENT) { /* create it and set this bootvar to active */
			size = 0;
			data = NULL;
		} else
			err(1, "efi_get_variable BootOrder");
	}

	/*
	 * We have BootOrder with the current order
	 * so grow the array by one, add the value
	 * and write the new variable value.
	 */
	size += sizeof(uint16_t);
	new = malloc(size);
	if (!new)
		err(1, "malloc");

	le16enc(new, val);
	if (size > sizeof(uint16_t))
		memcpy(new + sizeof(uint16_t), data, size - sizeof(uint16_t));

	if (set_bootvar("BootOrder", new, size) < 0)
		err(1, "set_bootvar");
	free(new);
}