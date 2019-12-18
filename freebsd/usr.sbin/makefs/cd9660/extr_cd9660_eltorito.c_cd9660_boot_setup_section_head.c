#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* platform_id; scalar_t__* num_section_entries; int /*<<< orphan*/ * header_indicator; } ;
struct TYPE_3__ {TYPE_2__ SH; } ;
struct boot_catalog_entry {TYPE_1__ entry_data; int /*<<< orphan*/  entry_type; } ;
typedef  TYPE_2__ boot_catalog_section_header ;

/* Variables and functions */
 int /*<<< orphan*/  ET_ENTRY_SH ; 
 int /*<<< orphan*/  ET_SECTION_HEADER_MORE ; 
 struct boot_catalog_entry* cd9660_init_boot_catalog_entry () ; 

__attribute__((used)) static struct boot_catalog_entry *
cd9660_boot_setup_section_head(char platform)
{
	struct boot_catalog_entry *entry;
	boot_catalog_section_header *sh;

	entry = cd9660_init_boot_catalog_entry();
	if (entry == NULL)
		return NULL;

	entry->entry_type = ET_ENTRY_SH;
	sh = &entry->entry_data.SH;
	/*
	 * More by default.
	 * The last one will manually be set to ET_SECTION_HEADER_LAST
	 */
	sh->header_indicator[0] = ET_SECTION_HEADER_MORE;
	sh->platform_id[0] = platform;
	sh->num_section_entries[0] = 0;
	return entry;
}