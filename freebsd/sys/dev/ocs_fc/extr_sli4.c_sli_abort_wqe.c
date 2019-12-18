#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
struct TYPE_5__ {int ia; int ir; int /*<<< orphan*/  cmd_type; void* cq_id; int /*<<< orphan*/  qosd; void* request_tag; int /*<<< orphan*/  command; void* t_tag; void* t_mask; int /*<<< orphan*/  criteria; } ;
typedef  TYPE_2__ sli4_abort_wqe_t ;
typedef  int sli4_abort_type_e ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_ABORT_CRITERIA_ABORT_TAG ; 
 int /*<<< orphan*/  SLI4_ABORT_CRITERIA_REQUEST_TAG ; 
 int /*<<< orphan*/  SLI4_ABORT_CRITERIA_XRI_TAG ; 
 int /*<<< orphan*/  SLI4_CMD_ABORT_WQE ; 
 int /*<<< orphan*/  SLI4_WQE_ABORT ; 
#define  SLI_ABORT_ABORT_ID 130 
#define  SLI_ABORT_REQUEST_ID 129 
#define  SLI_ABORT_XRI 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ocs_log_warn (int /*<<< orphan*/ ,char*,void*,void*) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_abort_wqe(sli4_t *sli4, void *buf, size_t size, sli4_abort_type_e type, uint32_t send_abts,
	      uint32_t ids, uint32_t mask, uint16_t tag, uint16_t cq_id)
{
	sli4_abort_wqe_t	*abort = buf;

	ocs_memset(buf, 0, size);

	switch (type) {
	case SLI_ABORT_XRI:
		abort->criteria = SLI4_ABORT_CRITERIA_XRI_TAG;
		if (mask) {
			ocs_log_warn(sli4->os, "warning non-zero mask %#x when aborting XRI %#x\n", mask, ids);
			mask = 0;
		}
		break;
	case SLI_ABORT_ABORT_ID:
		abort->criteria = SLI4_ABORT_CRITERIA_ABORT_TAG;
		break;
	case SLI_ABORT_REQUEST_ID:
		abort->criteria = SLI4_ABORT_CRITERIA_REQUEST_TAG;
		break;
	default:
		ocs_log_test(sli4->os, "unsupported type %#x\n", type);
		return -1;
	}

	abort->ia = send_abts ? 0 : 1;

	/* Suppress ABTS retries */
	abort->ir = 1;

	abort->t_mask = mask;
	abort->t_tag  = ids;
	abort->command = SLI4_WQE_ABORT;
	abort->request_tag = tag;
	abort->qosd = TRUE;
	abort->cq_id = cq_id;
	abort->cmd_type = SLI4_CMD_ABORT_WQE;

	return 0;
}