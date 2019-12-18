#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct outputter {int /*<<< orphan*/  (* output_entry ) (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* output_section ) (int /*<<< orphan*/ *,char const*,TYPE_1__*) ;} ;
struct TYPE_3__ {scalar_t__* num_section_entries; int /*<<< orphan*/ * platform_id; } ;
typedef  TYPE_1__ boot_catalog_section_header ;
typedef  int /*<<< orphan*/  boot_catalog_section_entry ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ET_BOOT_ENTRY_SIZE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dump_section(char *buffer, size_t offset, FILE *outfile, const char *filename,
    struct outputter *outputter)
{
	boot_catalog_section_header *sh;
	u_char platform_id;
	int i;
	size_t entry_offset;
	boot_catalog_section_entry *entry;

	sh = (boot_catalog_section_header *)&buffer[offset];
	if (outputter->output_section != NULL) {
		outputter->output_section(outfile, filename, sh);
	}

	platform_id = sh->platform_id[0];

	if (outputter->output_entry != NULL) {
		for (i = 1; i <= (int)sh->num_section_entries[0]; i++) {
			entry_offset = offset + i * ET_BOOT_ENTRY_SIZE;
			entry =
			    (boot_catalog_section_entry *)&buffer[entry_offset];
			outputter->output_entry(outfile, filename, entry,
			    platform_id, false);
		}
	}

	return (1 + (int)sh->num_section_entries[0]);
}