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
struct TYPE_2__ {int /*<<< orphan*/  pointer; } ;
union acpi_object {TYPE_1__ string; } ;
struct tpm_chip {int /*<<< orphan*/  groups_cnt; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  ppi_version; int /*<<< orphan*/  acpi_dev_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 
 int TPM_PPI_FN_VERSION ; 
 int /*<<< orphan*/  TPM_PPI_REVISION_ID_1 ; 
 int /*<<< orphan*/  acpi_check_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 union acpi_object* acpi_evaluate_dsm_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppi_attr_grp ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tpm_ppi_guid ; 

void tpm_add_ppi(struct tpm_chip *chip)
{
	union acpi_object *obj;

	if (!chip->acpi_dev_handle)
		return;

	if (!acpi_check_dsm(chip->acpi_dev_handle, &tpm_ppi_guid,
			    TPM_PPI_REVISION_ID_1, 1 << TPM_PPI_FN_VERSION))
		return;

	/* Cache PPI version string. */
	obj = acpi_evaluate_dsm_typed(chip->acpi_dev_handle, &tpm_ppi_guid,
				      TPM_PPI_REVISION_ID_1,
				      TPM_PPI_FN_VERSION,
				      NULL, ACPI_TYPE_STRING);
	if (obj) {
		strlcpy(chip->ppi_version, obj->string.pointer,
			sizeof(chip->ppi_version));
		ACPI_FREE(obj);
	}

	chip->groups[chip->groups_cnt++] = &ppi_attr_grp;
}