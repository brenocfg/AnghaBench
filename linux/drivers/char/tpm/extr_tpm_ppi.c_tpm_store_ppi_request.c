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
struct TYPE_6__ {int value; } ;
struct TYPE_5__ {int count; } ;
struct TYPE_4__ {int length; int /*<<< orphan*/ * pointer; } ;
union acpi_object {TYPE_3__ integer; void* type; TYPE_2__ package; TYPE_1__ buffer; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct tpm_chip {int /*<<< orphan*/  acpi_dev_handle; int /*<<< orphan*/  ppi_version; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 union acpi_object ACPI_INIT_DSM_ARGV4 (int,union acpi_object*) ; 
 void* ACPI_TYPE_BUFFER ; 
 void* ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EPERM ; 
 int TPM_PPI_FN_SUBREQ ; 
 int TPM_PPI_FN_SUBREQ2 ; 
 int TPM_PPI_REVISION_ID_1 ; 
 int TPM_PPI_REVISION_ID_2 ; 
 scalar_t__ acpi_check_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int sscanf (char const*,char*,int*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct tpm_chip* to_tpm_chip (struct device*) ; 
 union acpi_object* tpm_eval_dsm (int /*<<< orphan*/ ,int,void*,union acpi_object*,int) ; 
 int /*<<< orphan*/  tpm_ppi_guid ; 

__attribute__((used)) static ssize_t tpm_store_ppi_request(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	u32 req;
	u64 ret;
	int func = TPM_PPI_FN_SUBREQ;
	union acpi_object *obj, tmp[2];
	union acpi_object argv4 = ACPI_INIT_DSM_ARGV4(2, tmp);
	struct tpm_chip *chip = to_tpm_chip(dev);
	u64 rev = TPM_PPI_REVISION_ID_1;

	/*
	 * the function to submit TPM operation request to pre-os environment
	 * is updated with function index from SUBREQ to SUBREQ2 since PPI
	 * version 1.1
	 */
	if (acpi_check_dsm(chip->acpi_dev_handle, &tpm_ppi_guid,
			   TPM_PPI_REVISION_ID_1, 1 << TPM_PPI_FN_SUBREQ2))
		func = TPM_PPI_FN_SUBREQ2;

	/*
	 * PPI spec defines params[3].type as ACPI_TYPE_PACKAGE. Some BIOS
	 * accept buffer/string/integer type, but some BIOS accept buffer/
	 * string/package type. For PPI version 1.0 and 1.1, use buffer type
	 * for compatibility, and use package type since 1.2 according to spec.
	 */
	if (strcmp(chip->ppi_version, "1.3") == 0) {
		if (sscanf(buf, "%llu %llu", &tmp[0].integer.value,
			   &tmp[1].integer.value) != 2)
			goto ppi12;
		rev = TPM_PPI_REVISION_ID_2;
		tmp[0].type = ACPI_TYPE_INTEGER;
		tmp[1].type = ACPI_TYPE_INTEGER;
	} else if (strcmp(chip->ppi_version, "1.2") < 0) {
		if (sscanf(buf, "%d", &req) != 1)
			return -EINVAL;
		argv4.type = ACPI_TYPE_BUFFER;
		argv4.buffer.length = sizeof(req);
		argv4.buffer.pointer = (u8 *)&req;
	} else {
ppi12:
		argv4.package.count = 1;
		tmp[0].type = ACPI_TYPE_INTEGER;
		if (sscanf(buf, "%llu", &tmp[0].integer.value) != 1)
			return -EINVAL;
	}

	obj = tpm_eval_dsm(chip->acpi_dev_handle, func, ACPI_TYPE_INTEGER,
			   &argv4, rev);
	if (!obj) {
		return -ENXIO;
	} else {
		ret = obj->integer.value;
		ACPI_FREE(obj);
	}

	if (ret == 0)
		return (acpi_status)count;

	return (ret == 1) ? -EPERM : -EFAULT;
}