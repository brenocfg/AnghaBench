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
typedef  int u64 ;
struct TYPE_3__ {int bit_offset; } ;
struct acpi_whea_header {int mask; int flags; TYPE_1__ register_region; } ;

/* Variables and functions */
 int APEI_EXEC_PRESERVE_REGISTER ; 
 int apei_read (int*,TYPE_1__*) ; 
 int apei_write (int,TYPE_1__*) ; 

int __apei_exec_write_register(struct acpi_whea_header *entry, u64 val)
{
	int rc;

	val &= entry->mask;
	val <<= entry->register_region.bit_offset;
	if (entry->flags & APEI_EXEC_PRESERVE_REGISTER) {
		u64 valr = 0;
		rc = apei_read(&valr, &entry->register_region);
		if (rc)
			return rc;
		valr &= ~(entry->mask << entry->register_region.bit_offset);
		val |= valr;
	}
	rc = apei_write(val, &entry->register_region);

	return rc;
}