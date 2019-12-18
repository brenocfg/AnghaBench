#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_9__ {char* status; int /*<<< orphan*/  semaphore; int /*<<< orphan*/  preferred_d_id; int /*<<< orphan*/  hard_alpa; int /*<<< orphan*/ * wwnn; int /*<<< orphan*/ * wwpn; } ;
typedef  TYPE_2__ ocs_mgmt_get_nvparms_result_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ ENXIO ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_SEM_FOREVER ; 
 scalar_t__ ocs_hw_get_nvparms (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ocs_hw_set_nvparms (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  ocs_mgmt_get_nvparms_cb ; 
 int /*<<< orphan*/  ocs_mgmt_set_nvparms_cb ; 
 int /*<<< orphan*/  ocs_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ocs_sem_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ocs_sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ocs_strcmp (char*,char*) ; 
 char* ocs_strsep (char**,char*) ; 

__attribute__((used)) static int32_t
set_nv_wwn(ocs_t *ocs, char *name, char *wwn_p)
{
	ocs_mgmt_get_nvparms_result_t result;
	uint8_t new_wwpn[8];
	uint8_t new_wwnn[8];
	char *wwpn_p = NULL;
	char *wwnn_p = NULL;
	int32_t rc = -1;
	int wwpn = 0;
	int wwnn = 0;
	int i;

	/* This is a read-modify-write operation, so first we have to read
	 * the current values
	 */
	ocs_sem_init(&(result.semaphore), 0, "set_nv_wwn1");

	rc = ocs_hw_get_nvparms(&ocs->hw, ocs_mgmt_get_nvparms_cb, &result);

	if (rc == OCS_HW_RTN_SUCCESS) {
		if (ocs_sem_p(&(result.semaphore), OCS_SEM_FOREVER) != 0) {
			/* Undefined failure */
			ocs_log_err(ocs, "ocs_sem_p failed\n");
			return -ENXIO;
		}
		if (result.status != 0) {
			ocs_log_test(ocs, "getting nvparms status 0x%x\n", result.status);
			return -1;
		}
	}

	/* wwn_p contains wwpn_p@wwnn_p values */
	if (wwn_p != NULL) {
		wwpn_p = ocs_strsep(&wwn_p, "@");
		wwnn_p = wwn_p;
	}

	if (wwpn_p != NULL) {
		wwpn = ocs_strcmp(wwpn_p, "NA");
	}

	if (wwnn_p != NULL) {
		wwnn = ocs_strcmp(wwnn_p, "NA");
	}

	/* Parse the new WWPN */
	if ((wwpn_p != NULL) && (wwpn != 0)) {
		if (ocs_sscanf(wwpn_p, "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
				&(new_wwpn[0]), &(new_wwpn[1]), &(new_wwpn[2]),
				&(new_wwpn[3]), &(new_wwpn[4]), &(new_wwpn[5]),
				&(new_wwpn[6]), &(new_wwpn[7])) != 8) {
			ocs_log_test(ocs, "can't parse WWPN %s\n", wwpn_p);
			return -1;
		}
	}

	/* Parse the new WWNN */
	if ((wwnn_p != NULL) && (wwnn != 0 )) {
		if (ocs_sscanf(wwnn_p, "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
				&(new_wwnn[0]), &(new_wwnn[1]), &(new_wwnn[2]),
				&(new_wwnn[3]), &(new_wwnn[4]), &(new_wwnn[5]),
				&(new_wwnn[6]), &(new_wwnn[7])) != 8) {
			ocs_log_test(ocs, "can't parse WWNN %s\n", wwnn_p);
			return -1;
		}
	}

	for (i = 0; i < 8; i++) {
		/* Use active wwpn, if new one is not provided */
		if (wwpn == 0) {
			new_wwpn[i] = result.wwpn[i];
		}

		/* Use active wwnn, if new one is not provided */
		if (wwnn == 0) {
			new_wwnn[i] = result.wwnn[i];
		}
	}

	/* Modify the nv_wwnn and nv_wwpn, then write it back */
	ocs_sem_init(&(result.semaphore), 0, "set_nv_wwn2");

	rc = ocs_hw_set_nvparms(&ocs->hw, ocs_mgmt_set_nvparms_cb, new_wwpn,
				 new_wwnn, result.hard_alpa, result.preferred_d_id,
				 &result);
	if (rc == OCS_HW_RTN_SUCCESS) {
		if (ocs_sem_p(&(result.semaphore), OCS_SEM_FOREVER) != 0) {
			/* Undefined failure */
			ocs_log_err(ocs, "ocs_sem_p failed\n");
			return -ENXIO;
		}
		if (result.status != 0) {
			ocs_log_test(ocs, "setting wwn status 0x%x\n", result.status);
			return -1;
		}
	}

	return rc;
}