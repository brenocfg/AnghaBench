#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_15__ {scalar_t__ port_type; int /*<<< orphan*/  os; } ;
typedef  TYPE_3__ sli4_t ;
struct TYPE_13__ {scalar_t__ is_mq; } ;
struct TYPE_14__ {TYPE_1__ flag; } ;
struct TYPE_16__ {TYPE_2__ u; } ;
typedef  TYPE_4__ sli4_queue_t ;
typedef  int /*<<< orphan*/  sli4_qentry_e ;
struct TYPE_17__ {scalar_t__ ae; } ;
typedef  TYPE_5__ sli4_mcqe_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI_QENTRY_ASYNC ; 
 int /*<<< orphan*/  SLI_QENTRY_MQ ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int sli_cqe_mq (TYPE_5__*) ; 
 int sli_fc_cqe_parse (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

int32_t
sli_cq_parse(sli4_t *sli4, sli4_queue_t *cq, uint8_t *cqe, sli4_qentry_e *etype,
		uint16_t *q_id)
{
	int32_t	rc = 0;

	if (!sli4 || !cq || !cqe || !etype) {
		ocs_log_err(NULL, "bad parameters sli4=%p cq=%p cqe=%p etype=%p q_id=%p\n",
			    sli4, cq, cqe, etype, q_id);
		return -1;
	}

	if (cq->u.flag.is_mq) {
		sli4_mcqe_t	*mcqe = (void *)cqe;

		if (mcqe->ae) {
			*etype = SLI_QENTRY_ASYNC;
		} else {
			*etype = SLI_QENTRY_MQ;
			rc = sli_cqe_mq(mcqe);
		}
		*q_id = -1;
	} else if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		rc = sli_fc_cqe_parse(sli4, cq, cqe, etype, q_id);
	} else {
		ocs_log_test(sli4->os, "implement CQE parsing type = %#x\n",
			     sli4->port_type);
		rc = -1;
	}

	return rc;
}