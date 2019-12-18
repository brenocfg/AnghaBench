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
struct uuid_table {char* uuid_str; char* name; } ;

/* Variables and functions */
 int efi_known_guid (struct uuid_table**) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static void
print_known_guid(void)
{
	struct uuid_table *tbl;
	int i, n;

	n = efi_known_guid(&tbl);
	for (i = 0; i < n; i++)
		printf("%s %s\n", tbl[i].uuid_str, tbl[i].name);
}