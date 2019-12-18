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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  semaphore; int /*<<< orphan*/  preferred_d_id; int /*<<< orphan*/  hard_alpa; int /*<<< orphan*/  wwnn; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ ocs_mgmt_get_nvparms_result_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_sem_v (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_mgmt_get_nvparms_cb(int32_t status, uint8_t *wwpn, uint8_t *wwnn, uint8_t hard_alpa,
		uint32_t preferred_d_id, void *ul_arg)
{
	ocs_mgmt_get_nvparms_result_t *result = ul_arg;

	result->status = status;
	ocs_memcpy(result->wwpn, wwpn, sizeof(result->wwpn));
	ocs_memcpy(result->wwnn, wwnn, sizeof(result->wwnn));
	result->hard_alpa = hard_alpa;
	result->preferred_d_id = preferred_d_id;

	ocs_sem_v(&(result->semaphore));
}