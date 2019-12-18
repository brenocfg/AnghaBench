#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct acpi_table_header {int /*<<< orphan*/  signature; } ;
struct TYPE_5__ {int mode; } ;
struct TYPE_4__ {TYPE_2__ attr; int /*<<< orphan*/  read; } ;
struct acpi_data_attr {TYPE_1__ attr; } ;
struct TYPE_6__ {int (* fn ) (struct acpi_table_header*,struct acpi_data_attr*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_ACPI_DATA_OBJS ; 
 TYPE_3__* acpi_data_objs ; 
 int /*<<< orphan*/  acpi_data_show ; 
 struct acpi_data_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct acpi_table_header*,struct acpi_data_attr*) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

__attribute__((used)) static int acpi_table_data_init(struct acpi_table_header *th)
{
	struct acpi_data_attr *data_attr;
	int i;

	for (i = 0; i < NUM_ACPI_DATA_OBJS; i++) {
		if (ACPI_COMPARE_NAMESEG(th->signature, acpi_data_objs[i].name)) {
			data_attr = kzalloc(sizeof(*data_attr), GFP_KERNEL);
			if (!data_attr)
				return -ENOMEM;
			sysfs_attr_init(&data_attr->attr.attr);
			data_attr->attr.read = acpi_data_show;
			data_attr->attr.attr.mode = 0400;
			return acpi_data_objs[i].fn(th, data_attr);
		}
	}
	return 0;
}