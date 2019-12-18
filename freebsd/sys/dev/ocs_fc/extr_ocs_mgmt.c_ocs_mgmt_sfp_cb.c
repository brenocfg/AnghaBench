#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_3__ {int running; int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  semaphore; int /*<<< orphan*/  page_data; int /*<<< orphan*/  bytes_read; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ ocs_mgmt_sfp_result_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SFP_PAGE_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_sem_v (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_mgmt_sfp_cb(void *os, int32_t status, uint32_t bytes_read, uint32_t *data, void *arg)
{
	ocs_mgmt_sfp_result_t *result = arg;
	ocs_t *ocs = os;

	ocs_lock(&(result->cb_lock));
	result->running++;
	if(result->running == 2) {
		/* get_sfp() has timed out */
		ocs_unlock(&(result->cb_lock));
		ocs_free(ocs, result, sizeof(ocs_mgmt_sfp_result_t));
		return;
	}

	result->status = status;
	result->bytes_read = bytes_read;
	ocs_memcpy(&result->page_data, data, SFP_PAGE_SIZE);

	ocs_sem_v(&(result->semaphore));
	ocs_unlock(&(result->cb_lock));
}