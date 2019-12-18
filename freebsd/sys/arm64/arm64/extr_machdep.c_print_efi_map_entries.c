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
struct efi_map_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  foreach_efi_map_entry (struct efi_map_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_efi_map_entry ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void
print_efi_map_entries(struct efi_map_header *efihdr)
{

	printf("%23s %12s %12s %8s %4s\n",
	    "Type", "Physical", "Virtual", "#Pages", "Attr");
	foreach_efi_map_entry(efihdr, print_efi_map_entry);
}