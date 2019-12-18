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
 int /*<<< orphan*/  print_var (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
print_variable(char *name)
{
	char *vname;
	efi_guid_t guid;

	breakdown_name(name, &guid, &vname);
	print_var(&guid, vname);
}