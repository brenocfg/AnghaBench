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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_table_header {int dummy; } ;
struct acpi_pptt_processor {int dummy; } ;

/* Variables and functions */
 scalar_t__ fetch_pptt_subtable (struct acpi_table_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct acpi_pptt_processor *fetch_pptt_node(struct acpi_table_header *table_hdr,
						   u32 pptt_ref)
{
	return (struct acpi_pptt_processor *)fetch_pptt_subtable(table_hdr, pptt_ref);
}