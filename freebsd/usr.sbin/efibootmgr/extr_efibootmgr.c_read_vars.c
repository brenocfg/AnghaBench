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
struct entry {int /*<<< orphan*/  idx; int /*<<< orphan*/  guid; int /*<<< orphan*/  attrs; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_GLOBAL_GUID ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct entry*,int /*<<< orphan*/ ) ; 
 int efi_get_next_variable_name (int /*<<< orphan*/ **,char**) ; 
 int efi_get_variable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ efi_guid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efivars ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 struct entry* malloc (int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
read_vars(void)
{

	efi_guid_t *guid;
	char *next_name = NULL;
	int ret = 0;

	struct entry *nent;

	LIST_INIT(&efivars);
	while ((ret = efi_get_next_variable_name(&guid, &next_name)) > 0) {
		/*
		 * Only pay attention to EFI:BootXXXX variables to get the list.
		 */
		if (efi_guid_cmp(guid, &EFI_GLOBAL_GUID) != 0 ||
		    strlen(next_name) != 8 ||
		    strncmp(next_name, "Boot", 4) != 0 ||
		    !isxdigit(next_name[4]) ||
		    !isxdigit(next_name[5]) ||
		    !isxdigit(next_name[6]) ||
		    !isxdigit(next_name[7]))
			continue;
		nent = malloc(sizeof(struct entry));
		nent->name = strdup(next_name);

		ret = efi_get_variable(*guid, next_name, &nent->data,
		    &nent->size, &nent->attrs);
		if (ret < 0)
			err(1, "efi_get_variable");
		nent->guid = *guid;
		nent->idx = strtoul(&next_name[4], NULL, 16);
		LIST_INSERT_HEAD(&efivars, nent, entries);
	}
}