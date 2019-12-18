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
struct TYPE_2__ {int length; } ;
struct acpi_table_erst {int header_length; int entries; TYPE_1__ header; } ;
struct acpi_erst_entry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int erst_check_table(struct acpi_table_erst *erst_tab)
{
	if ((erst_tab->header_length !=
	     (sizeof(struct acpi_table_erst) - sizeof(erst_tab->header)))
	    && (erst_tab->header_length != sizeof(struct acpi_table_erst)))
		return -EINVAL;
	if (erst_tab->header.length < sizeof(struct acpi_table_erst))
		return -EINVAL;
	if (erst_tab->entries !=
	    (erst_tab->header.length - sizeof(struct acpi_table_erst)) /
	    sizeof(struct acpi_erst_entry))
		return -EINVAL;

	return 0;
}