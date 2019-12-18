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
struct TYPE_3__ {int /*<<< orphan*/ * pointer; int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
union acpi_object {TYPE_2__ integer; TYPE_1__ buffer; } ;
typedef  int u32 ;
struct tpm_chip {int /*<<< orphan*/  acpi_dev_handle; int /*<<< orphan*/  ppi_version; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TPM_PPI_FN_GETACT ; 
 int /*<<< orphan*/  TPM_PPI_REVISION_ID_1 ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct tpm_chip* to_tpm_chip (struct device*) ; 
 union acpi_object* tpm_eval_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union acpi_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t tpm_show_ppi_transition_action(struct device *dev,
					      struct device_attribute *attr,
					      char *buf)
{
	u32 ret;
	acpi_status status;
	union acpi_object *obj = NULL;
	union acpi_object tmp = {
		.buffer.type = ACPI_TYPE_BUFFER,
		.buffer.length = 0,
		.buffer.pointer = NULL
	};
	struct tpm_chip *chip = to_tpm_chip(dev);

	static char *info[] = {
		"None",
		"Shutdown",
		"Reboot",
		"OS Vendor-specific",
		"Error",
	};

	/*
	 * PPI spec defines params[3].type as empty package, but some platforms
	 * (e.g. Capella with PPI 1.0) need integer/string/buffer type, so for
	 * compatibility, define params[3].type as buffer, if PPI version < 1.2
	 */
	if (strcmp(chip->ppi_version, "1.2") < 0)
		obj = &tmp;
	obj = tpm_eval_dsm(chip->acpi_dev_handle, TPM_PPI_FN_GETACT,
			   ACPI_TYPE_INTEGER, obj, TPM_PPI_REVISION_ID_1);
	if (!obj) {
		return -ENXIO;
	} else {
		ret = obj->integer.value;
		ACPI_FREE(obj);
	}

	if (ret < ARRAY_SIZE(info) - 1)
		status = scnprintf(buf, PAGE_SIZE, "%d: %s\n", ret, info[ret]);
	else
		status = scnprintf(buf, PAGE_SIZE, "%d: %s\n", ret,
				   info[ARRAY_SIZE(info)-1]);
	return status;
}