#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
struct TYPE_6__ {int major_code; int /*<<< orphan*/  minor_code; int /*<<< orphan*/  resource_id; } ;
typedef  TYPE_2__ sli4_eqe_t ;
typedef  int int32_t ;

/* Variables and functions */
#define  SLI4_MAJOR_CODE_SENTINEL 129 
#define  SLI4_MAJOR_CODE_STANDARD 128 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

int32_t
sli_eq_parse(sli4_t *sli4, uint8_t *buf, uint16_t *cq_id)
{
	sli4_eqe_t	*eqe = (void *)buf;
	int32_t		rc = 0;

	if (!sli4 || !buf || !cq_id) {
		ocs_log_err(NULL, "bad parameters sli4=%p buf=%p cq_id=%p\n",
				sli4, buf, cq_id);
		return -1;
	}

	switch (eqe->major_code) {
	case SLI4_MAJOR_CODE_STANDARD:
		*cq_id = eqe->resource_id;
		break;
	case SLI4_MAJOR_CODE_SENTINEL:
		ocs_log_debug(sli4->os, "sentinel EQE\n");
		rc = 1;
		break;
	default:
		ocs_log_test(sli4->os, "Unsupported EQE: major %x minor %x\n",
				eqe->major_code, eqe->minor_code);
		rc = -1;
	}

	return rc;
}