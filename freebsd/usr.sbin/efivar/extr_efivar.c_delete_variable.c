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
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  breakdown_name (char*,int /*<<< orphan*/ *,char**) ; 
 scalar_t__ efi_del_variable (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 

__attribute__((used)) static void
delete_variable(char *name)
{
	char *vname;
	efi_guid_t guid;

	breakdown_name(name, &guid, &vname);
	if (efi_del_variable(guid, vname) < 0)
		err(1, "efi_del_variable");
}