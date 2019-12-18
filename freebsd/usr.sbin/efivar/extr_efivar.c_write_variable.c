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
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  attrib ; 
 int /*<<< orphan*/  breakdown_name (char*,int /*<<< orphan*/ *,char**) ; 
 scalar_t__ efi_set_variable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * get_value (char*,size_t*) ; 

__attribute__((used)) static void
write_variable(char *name, char *val)
{
	char *vname;
	efi_guid_t guid;
	size_t datalen;
	uint8_t *data;

	breakdown_name(name, &guid, &vname);
	data = get_value(val, &datalen);
	if (efi_set_variable(guid, vname, data, datalen, attrib) < 0)
		err(1, "efi_set_variable");
}