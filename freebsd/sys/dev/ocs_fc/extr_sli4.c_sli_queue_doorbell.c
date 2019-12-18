#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  os; int /*<<< orphan*/  port_type; } ;
typedef  TYPE_3__ sli4_t ;
struct TYPE_7__ {int /*<<< orphan*/  rq_batch; int /*<<< orphan*/  is_hdr; } ;
struct TYPE_8__ {TYPE_1__ flag; } ;
struct TYPE_10__ {int type; int n_posted; int index; int /*<<< orphan*/  doorbell_offset; int /*<<< orphan*/  doorbell_rset; int /*<<< orphan*/  id; TYPE_2__ u; } ;
typedef  TYPE_4__ sli4_queue_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SLI4_MQ_DOORBELL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLI4_PORT_TYPE_FC ; 
 int SLI4_QUEUE_RQ_BATCH ; 
 int SLI4_RQ_DOORBELL (int,int /*<<< orphan*/ ) ; 
 int SLI4_WQ_DOORBELL (int,int,int /*<<< orphan*/ ) ; 
#define  SLI_QTYPE_CQ 132 
#define  SLI_QTYPE_EQ 131 
#define  SLI_QTYPE_MQ 130 
#define  SLI_QTYPE_RQ 129 
#define  SLI_QTYPE_WQ 128 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ocs_reg_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sli_cq_doorbell (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sli_eq_doorbell (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
sli_queue_doorbell(sli4_t *sli4, sli4_queue_t *q)
{
	uint32_t	val = 0;

	switch (q->type) {
	case SLI_QTYPE_EQ:
		val = sli_eq_doorbell(q->n_posted, q->id, FALSE);
		ocs_reg_write32(sli4->os, q->doorbell_rset, q->doorbell_offset, val);
		break;
	case SLI_QTYPE_CQ:
		val = sli_cq_doorbell(q->n_posted, q->id, FALSE);
		ocs_reg_write32(sli4->os, q->doorbell_rset, q->doorbell_offset, val);
		break;
	case SLI_QTYPE_MQ:
		val = SLI4_MQ_DOORBELL(q->n_posted, q->id);
		ocs_reg_write32(sli4->os, q->doorbell_rset, q->doorbell_offset, val);
		break;
	case SLI_QTYPE_RQ:
	{
		uint32_t	n_posted = q->n_posted;
		/*
		 * FC/FCoE has different rules for Receive Queues. The host
		 * should only update the doorbell of the RQ-pair containing
		 * the headers since the header / payload RQs are treated
		 * as a matched unit.
		 */
		if (SLI4_PORT_TYPE_FC == sli4->port_type) {
			/*
			 * In RQ-pair, an RQ either contains the FC header
			 * (i.e. is_hdr == TRUE) or the payload.
			 *
			 * Don't ring doorbell for payload RQ
			 */
			if (!q->u.flag.is_hdr) {
				break;
			}
			/*
			 * Some RQ cannot be incremented one entry at a time. Instead,
			 * the driver collects a number of entries and updates the
			 * RQ in batches.
			 */
			if (q->u.flag.rq_batch) {
				if (((q->index + q->n_posted) % SLI4_QUEUE_RQ_BATCH)) {
					break;
				}
				n_posted = SLI4_QUEUE_RQ_BATCH;
			}
		}

		val = SLI4_RQ_DOORBELL(n_posted, q->id);
		ocs_reg_write32(sli4->os, q->doorbell_rset, q->doorbell_offset, val);
		break;
	}
	case SLI_QTYPE_WQ:
		val = SLI4_WQ_DOORBELL(q->n_posted, q->index, q->id);
		ocs_reg_write32(sli4->os, q->doorbell_rset, q->doorbell_offset, val);
		break;
	default:
		ocs_log_test(sli4->os, "bad queue type %d\n", q->type);
		return -1;
	}

	return 0;
}