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
typedef  size_t u32 ;
struct acpi_table_header {int /*<<< orphan*/  signature; int /*<<< orphan*/  oem_table_id; int /*<<< orphan*/  oem_id; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {size_t current_table_count; TYPE_2__* tables; } ;
struct TYPE_5__ {TYPE_1__* pointer; int /*<<< orphan*/  signature; } ;
struct TYPE_4__ {int /*<<< orphan*/ * oem_table_id; int /*<<< orphan*/ * oem_id; int /*<<< orphan*/ * signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COPY_NAMESEG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ACPI_DB_TABLES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_TABLES ; 
 scalar_t__ ACPI_NAMESEG_SIZE ; 
 scalar_t__ ACPI_OEM_ID_SIZE ; 
 scalar_t__ ACPI_OEM_TABLE_ID_SIZE ; 
 int /*<<< orphan*/  AE_AML_STRING_LIMIT ; 
 int /*<<< orphan*/  AE_BAD_SIGNATURE ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_3__ acpi_gbl_root_table_list ; 
 int /*<<< orphan*/  acpi_tb_validate_table (TYPE_2__*) ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_valid_nameseg (char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct acpi_table_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  tb_find_table ; 

acpi_status
acpi_tb_find_table(char *signature,
		   char *oem_id, char *oem_table_id, u32 *table_index)
{
	acpi_status status = AE_OK;
	struct acpi_table_header header;
	u32 i;

	ACPI_FUNCTION_TRACE(tb_find_table);

	/* Validate the input table signature */

	if (!acpi_ut_valid_nameseg(signature)) {
		return_ACPI_STATUS(AE_BAD_SIGNATURE);
	}

	/* Don't allow the OEM strings to be too long */

	if ((strlen(oem_id) > ACPI_OEM_ID_SIZE) ||
	    (strlen(oem_table_id) > ACPI_OEM_TABLE_ID_SIZE)) {
		return_ACPI_STATUS(AE_AML_STRING_LIMIT);
	}

	/* Normalize the input strings */

	memset(&header, 0, sizeof(struct acpi_table_header));
	ACPI_COPY_NAMESEG(header.signature, signature);
	strncpy(header.oem_id, oem_id, ACPI_OEM_ID_SIZE);
	strncpy(header.oem_table_id, oem_table_id, ACPI_OEM_TABLE_ID_SIZE);

	/* Search for the table */

	(void)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	for (i = 0; i < acpi_gbl_root_table_list.current_table_count; ++i) {
		if (memcmp(&(acpi_gbl_root_table_list.tables[i].signature),
			   header.signature, ACPI_NAMESEG_SIZE)) {

			/* Not the requested table */

			continue;
		}

		/* Table with matching signature has been found */

		if (!acpi_gbl_root_table_list.tables[i].pointer) {

			/* Table is not currently mapped, map it */

			status =
			    acpi_tb_validate_table(&acpi_gbl_root_table_list.
						   tables[i]);
			if (ACPI_FAILURE(status)) {
				goto unlock_and_exit;
			}

			if (!acpi_gbl_root_table_list.tables[i].pointer) {
				continue;
			}
		}

		/* Check for table match on all IDs */

		if (!memcmp
		    (acpi_gbl_root_table_list.tables[i].pointer->signature,
		     header.signature, ACPI_NAMESEG_SIZE) && (!oem_id[0]
							      ||
							      !memcmp
							      (acpi_gbl_root_table_list.
							       tables[i].
							       pointer->oem_id,
							       header.oem_id,
							       ACPI_OEM_ID_SIZE))
		    && (!oem_table_id[0]
			|| !memcmp(acpi_gbl_root_table_list.tables[i].pointer->
				   oem_table_id, header.oem_table_id,
				   ACPI_OEM_TABLE_ID_SIZE))) {
			*table_index = i;

			ACPI_DEBUG_PRINT((ACPI_DB_TABLES,
					  "Found table [%4.4s]\n",
					  header.signature));
			goto unlock_and_exit;
		}
	}
	status = AE_NOT_FOUND;

unlock_and_exit:
	(void)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	return_ACPI_STATUS(status);
}