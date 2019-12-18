#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_12__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_13__ {int running; scalar_t__ status; int bytes_read; int /*<<< orphan*/  page_data; int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  semaphore; } ;
typedef  TYPE_2__ ocs_mgmt_sfp_result_t ;
typedef  int int32_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENXIO ; 
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int /*<<< orphan*/  ocs_free (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_hw_get_sfp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock_init (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*,scalar_t__) ; 
 TYPE_2__* ocs_malloc (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ocs_memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_mgmt_sfp_cb ; 
 int /*<<< orphan*/  ocs_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ocs_sem_p (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
ocs_mgmt_get_sfp(ocs_t *ocs, uint16_t page, void *buf, uint32_t buf_len)
{
	int rc = 0;
	ocs_mgmt_sfp_result_t *result = ocs_malloc(ocs, sizeof(ocs_mgmt_sfp_result_t),  OCS_M_ZERO | OCS_M_NOWAIT);;

	ocs_sem_init(&(result->semaphore), 0, "get_sfp");
	ocs_lock_init(ocs, &(result->cb_lock), "get_sfp");

	/* Send the HW command */
	ocs_hw_get_sfp(&ocs->hw, page, ocs_mgmt_sfp_cb, result);

	/* Wait for semaphore to be signaled when the command completes */
	if (ocs_sem_p(&(result->semaphore), 5 * 1000 * 1000) != 0) {
		/* Timed out, callback will free memory */
		ocs_lock(&(result->cb_lock));
		result->running++;
		if(result->running == 1) {
			ocs_log_err(ocs, "ocs_sem_p failed\n");
			ocs_unlock(&(result->cb_lock));
			return (-ENXIO);
		}
		/* sfp_cb() has already executed, proceed as normal */
		ocs_unlock(&(result->cb_lock));
	}

	/* Check status */
	if (result->status != 0) {
		ocs_log_test(ocs, "read_transceiver_data returned status %d\n",
			     result->status);
		rc = -EFAULT;
	}

	if (rc == 0) {
		rc = (result->bytes_read > buf_len ? buf_len : result->bytes_read);
		/* Copy the results back to the supplied buffer */
		ocs_memcpy(buf, result->page_data, rc);
	}

	ocs_free(ocs, result, sizeof(ocs_mgmt_sfp_result_t));
	return rc;
}