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
struct TYPE_2__ {int value; int /*<<< orphan*/  type; } ;
union acpi_object {TYPE_1__ integer; } ;
typedef  int u32 ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 union acpi_object ACPI_INIT_DSM_ARGV4 (int,union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int ARRAY_SIZE (char**) ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int TPM_PPI_FN_GETOPR ; 
 int /*<<< orphan*/  TPM_PPI_REVISION_ID_1 ; 
 int /*<<< orphan*/  acpi_check_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int,int,char*) ; 
 union acpi_object* tpm_eval_dsm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,union acpi_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_ppi_guid ; 

__attribute__((used)) static ssize_t show_ppi_operations(acpi_handle dev_handle, char *buf, u32 start,
				   u32 end)
{
	int i;
	u32 ret;
	char *str = buf;
	union acpi_object *obj, tmp;
	union acpi_object argv = ACPI_INIT_DSM_ARGV4(1, &tmp);

	static char *info[] = {
		"Not implemented",
		"BIOS only",
		"Blocked for OS by BIOS",
		"User required",
		"User not required",
	};

	if (!acpi_check_dsm(dev_handle, &tpm_ppi_guid, TPM_PPI_REVISION_ID_1,
			    1 << TPM_PPI_FN_GETOPR))
		return -EPERM;

	tmp.integer.type = ACPI_TYPE_INTEGER;
	for (i = start; i <= end; i++) {
		tmp.integer.value = i;
		obj = tpm_eval_dsm(dev_handle, TPM_PPI_FN_GETOPR,
				   ACPI_TYPE_INTEGER, &argv,
				   TPM_PPI_REVISION_ID_1);
		if (!obj) {
			return -ENOMEM;
		} else {
			ret = obj->integer.value;
			ACPI_FREE(obj);
		}

		if (ret > 0 && ret < ARRAY_SIZE(info))
			str += scnprintf(str, PAGE_SIZE, "%d %d: %s\n",
					 i, ret, info[ret]);
	}

	return str - buf;
}