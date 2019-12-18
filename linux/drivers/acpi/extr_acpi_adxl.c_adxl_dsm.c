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
struct TYPE_4__ {int count; union acpi_object* elements; } ;
struct TYPE_3__ {int value; } ;
union acpi_object {int type; TYPE_2__ package; TYPE_1__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int ACPI_TYPE_INTEGER ; 
 int ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  ADXL_REVISION ; 
 union acpi_object* acpi_evaluate_dsm_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,union acpi_object*,int) ; 
 int /*<<< orphan*/  adxl_guid ; 
 int /*<<< orphan*/  handle ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

__attribute__((used)) static union acpi_object *adxl_dsm(int cmd, union acpi_object argv[])
{
	union acpi_object *obj, *o;

	obj = acpi_evaluate_dsm_typed(handle, &adxl_guid, ADXL_REVISION,
				      cmd, argv, ACPI_TYPE_PACKAGE);
	if (!obj) {
		pr_info("DSM call failed for cmd=%d\n", cmd);
		return NULL;
	}

	if (obj->package.count != 2) {
		pr_info("Bad pkg count %d\n", obj->package.count);
		goto err;
	}

	o = obj->package.elements;
	if (o->type != ACPI_TYPE_INTEGER) {
		pr_info("Bad 1st element type %d\n", o->type);
		goto err;
	}
	if (o->integer.value) {
		pr_info("Bad ret val %llu\n", o->integer.value);
		goto err;
	}

	o = obj->package.elements + 1;
	if (o->type != ACPI_TYPE_PACKAGE) {
		pr_info("Bad 2nd element type %d\n", o->type);
		goto err;
	}
	return obj;

err:
	ACPI_FREE(obj);
	return NULL;
}