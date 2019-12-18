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
struct TYPE_4__ {int value; } ;
struct TYPE_3__ {int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ package; } ;
typedef  int u64 ;
struct tpm_chip {int /*<<< orphan*/  acpi_dev_handle; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TPM_PPI_FN_GETRSP ; 
 int /*<<< orphan*/  TPM_PPI_REVISION_ID_1 ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 struct tpm_chip* to_tpm_chip (struct device*) ; 
 union acpi_object* tpm_eval_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t tpm_show_ppi_response(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	acpi_status status = -EINVAL;
	union acpi_object *obj, *ret_obj;
	u64 req, res;
	struct tpm_chip *chip = to_tpm_chip(dev);

	obj = tpm_eval_dsm(chip->acpi_dev_handle, TPM_PPI_FN_GETRSP,
			   ACPI_TYPE_PACKAGE, NULL, TPM_PPI_REVISION_ID_1);
	if (!obj)
		return -ENXIO;

	/*
	 * parameter output.pointer should be of package type, including
	 * 3 integers. The first means function return code, the second means
	 * most recent TPM operation request, and the last means response to
	 * the most recent TPM operation request. Only if the first is 0, and
	 * the second integer is not 0, the response makes sense.
	 */
	ret_obj = obj->package.elements;
	if (obj->package.count < 3 ||
	    ret_obj[0].type != ACPI_TYPE_INTEGER ||
	    ret_obj[1].type != ACPI_TYPE_INTEGER ||
	    ret_obj[2].type != ACPI_TYPE_INTEGER)
		goto cleanup;

	if (ret_obj[0].integer.value) {
		status = -EFAULT;
		goto cleanup;
	}

	req = ret_obj[1].integer.value;
	res = ret_obj[2].integer.value;
	if (req) {
		if (res == 0)
			status = scnprintf(buf, PAGE_SIZE, "%llu %s\n", req,
					   "0: Success");
		else if (res == 0xFFFFFFF0)
			status = scnprintf(buf, PAGE_SIZE, "%llu %s\n", req,
					   "0xFFFFFFF0: User Abort");
		else if (res == 0xFFFFFFF1)
			status = scnprintf(buf, PAGE_SIZE, "%llu %s\n", req,
					   "0xFFFFFFF1: BIOS Failure");
		else if (res >= 1 && res <= 0x00000FFF)
			status = scnprintf(buf, PAGE_SIZE, "%llu %llu: %s\n",
					   req, res, "Corresponding TPM error");
		else
			status = scnprintf(buf, PAGE_SIZE, "%llu %llu: %s\n",
					   req, res, "Error");
	} else {
		status = scnprintf(buf, PAGE_SIZE, "%llu: %s\n",
				   req, "No Recent Request");
	}

cleanup:
	ACPI_FREE(obj);
	return status;
}