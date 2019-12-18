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
typedef  char u8 ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;
struct TYPE_2__ {char* name; int (* validate ) (int /*<<< orphan*/ *,int,char*,unsigned long) ;int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ efi_guidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int,char*,unsigned long) ; 
 int /*<<< orphan*/  ucs2_as_utf8 (char*,int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long ucs2_utf8size (int /*<<< orphan*/ *) ; 
 scalar_t__ variable_matches (char*,unsigned long,char const*,int*) ; 
 TYPE_1__* variable_validate ; 

bool
efivar_validate(efi_guid_t vendor, efi_char16_t *var_name, u8 *data,
		unsigned long data_size)
{
	int i;
	unsigned long utf8_size;
	u8 *utf8_name;

	utf8_size = ucs2_utf8size(var_name);
	utf8_name = kmalloc(utf8_size + 1, GFP_KERNEL);
	if (!utf8_name)
		return false;

	ucs2_as_utf8(utf8_name, var_name, utf8_size);
	utf8_name[utf8_size] = '\0';

	for (i = 0; variable_validate[i].name[0] != '\0'; i++) {
		const char *name = variable_validate[i].name;
		int match = 0;

		if (efi_guidcmp(vendor, variable_validate[i].vendor))
			continue;

		if (variable_matches(utf8_name, utf8_size+1, name, &match)) {
			if (variable_validate[i].validate == NULL)
				break;
			kfree(utf8_name);
			return variable_validate[i].validate(var_name, match,
							     data, data_size);
		}
	}
	kfree(utf8_name);
	return true;
}