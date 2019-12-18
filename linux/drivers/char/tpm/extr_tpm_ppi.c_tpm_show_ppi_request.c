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
struct TYPE_6__ {int count; TYPE_2__* elements; } ;
union acpi_object {TYPE_3__ package; } ;
typedef  scalar_t__ u64 ;
struct tpm_chip {int /*<<< orphan*/  acpi_dev_handle; int /*<<< orphan*/  ppi_version; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TPM_PPI_FN_GETREQ ; 
 scalar_t__ TPM_PPI_REVISION_ID_1 ; 
 scalar_t__ TPM_PPI_REVISION_ID_2 ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct tpm_chip* to_tpm_chip (struct device*) ; 
 union acpi_object* tpm_eval_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ tpm_ppi_req_has_parameter (scalar_t__) ; 

__attribute__((used)) static ssize_t tpm_show_ppi_request(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	ssize_t size = -EINVAL;
	union acpi_object *obj;
	struct tpm_chip *chip = to_tpm_chip(dev);
	u64 rev = TPM_PPI_REVISION_ID_2;
	u64 req;

	if (strcmp(chip->ppi_version, "1.2") < 0)
		rev = TPM_PPI_REVISION_ID_1;

	obj = tpm_eval_dsm(chip->acpi_dev_handle, TPM_PPI_FN_GETREQ,
			   ACPI_TYPE_PACKAGE, NULL, rev);
	if (!obj)
		return -ENXIO;

	/*
	 * output.pointer should be of package type, including two integers.
	 * The first is function return code, 0 means success and 1 means
	 * error. The second is pending TPM operation requested by the OS, 0
	 * means none and >0 means operation value.
	 */
	if (obj->package.count == 3 &&
	    obj->package.elements[0].type == ACPI_TYPE_INTEGER &&
	    obj->package.elements[1].type == ACPI_TYPE_INTEGER &&
	    obj->package.elements[2].type == ACPI_TYPE_INTEGER) {
		if (obj->package.elements[0].integer.value)
			size = -EFAULT;
		else {
			req = obj->package.elements[1].integer.value;
			if (tpm_ppi_req_has_parameter(req))
				size = scnprintf(buf, PAGE_SIZE,
				    "%llu %llu\n", req,
				    obj->package.elements[2].integer.value);
			else
				size = scnprintf(buf, PAGE_SIZE,
						"%llu\n", req);
		}
	} else if (obj->package.count == 2 &&
	    obj->package.elements[0].type == ACPI_TYPE_INTEGER &&
	    obj->package.elements[1].type == ACPI_TYPE_INTEGER) {
		if (obj->package.elements[0].integer.value)
			size = -EFAULT;
		else
			size = scnprintf(buf, PAGE_SIZE, "%llu\n",
				 obj->package.elements[1].integer.value);
	}

	ACPI_FREE(obj);

	return size;
}