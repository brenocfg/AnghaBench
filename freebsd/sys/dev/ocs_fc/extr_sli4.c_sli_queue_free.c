#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_23__ {scalar_t__ virt; } ;
struct TYPE_24__ {scalar_t__ if_type; int /*<<< orphan*/ * os; TYPE_1__ bmbx; int /*<<< orphan*/  port_type; } ;
typedef  TYPE_2__ sli4_t ;
struct TYPE_25__ {int /*<<< orphan*/  additional_status; int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ sli4_res_hdr_t ;
struct TYPE_26__ {int type; struct TYPE_26__* id; int /*<<< orphan*/  dma; int /*<<< orphan*/  lock; } ;
typedef  TYPE_4__ sli4_queue_t ;
typedef  scalar_t__ (* sli4_destroy_q_fn_t ) (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 scalar_t__ SLI4_IF_TYPE_BE3_SKH_PF ; 
 int /*<<< orphan*/  SLI4_PORT_TYPE_FC ; 
 TYPE_2__** SLI_QNAME ; 
#define  SLI_QTYPE_CQ 132 
#define  SLI_QTYPE_EQ 131 
#define  SLI_QTYPE_MQ 130 
#define  SLI_QTYPE_RQ 129 
#define  SLI_QTYPE_WQ 128 
 scalar_t__ ocs_dma_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ *,char*,...) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  payload ; 
 int /*<<< orphan*/  sli4_cmd_sli_config_t ; 
 scalar_t__ sli_bmbx_command (TYPE_2__*) ; 
 scalar_t__ sli_cmd_common_destroy_cq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ sli_cmd_common_destroy_eq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ sli_cmd_common_destroy_mq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ sli_cmd_fcoe_rq_destroy (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ sli_cmd_fcoe_wq_destroy (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ sli_res_sli_config (scalar_t__) ; 

int32_t
sli_queue_free(sli4_t *sli4, sli4_queue_t *q, uint32_t destroy_queues, uint32_t free_memory)
{
	sli4_destroy_q_fn_t destroy = NULL;
	int32_t		rc = -1;

	if (!sli4 || !q) {
		ocs_log_err(NULL, "bad parameter sli4=%p q=%p\n", sli4, q);
		return -1;
	}

	if (destroy_queues) {
		switch (q->type) {
		case SLI_QTYPE_EQ:
			destroy = sli_cmd_common_destroy_eq;
			break;
		case SLI_QTYPE_CQ:
			destroy = sli_cmd_common_destroy_cq;
			break;
		case SLI_QTYPE_MQ:
			destroy = sli_cmd_common_destroy_mq;
			break;
		case SLI_QTYPE_WQ:
			if (SLI4_PORT_TYPE_FC == sli4->port_type) {
				destroy = sli_cmd_fcoe_wq_destroy;
			} else {
				/* TODO */
				ocs_log_test(sli4->os, "unsupported WQ destroy\n");
				return -1;
			}
			break;
		case SLI_QTYPE_RQ:
			if (SLI4_PORT_TYPE_FC == sli4->port_type) {
				destroy = sli_cmd_fcoe_rq_destroy;
			} else {
				/* TODO */
				ocs_log_test(sli4->os, "unsupported RQ destroy\n");
				return -1;
			}
			break;
		default:
			ocs_log_test(sli4->os, "bad queue type %d\n",
					q->type);
			return -1;
		}

		/*
		 * Destroying queues makes BE3 sad (version 0 interface type). Rely
		 * on COMMON_FUNCTION_RESET to free host allocated queue resources
		 * inside the SLI Port.
		 */
		if (SLI4_IF_TYPE_BE3_SKH_PF == sli4->if_type) {
			destroy = NULL;
		}

		/* Destroy the queue if the operation is defined */
		if (destroy && destroy(sli4, sli4->bmbx.virt, SLI4_BMBX_SIZE, q->id)) {
			sli4_res_hdr_t	*res = NULL;

			if (sli_bmbx_command(sli4)){
				ocs_log_crit(sli4->os, "bootstrap mailbox write fail destroy %s\n",
						SLI_QNAME[q->type]);
			} else if (sli_res_sli_config(sli4->bmbx.virt)) {
				ocs_log_err(sli4->os, "bad status destroy %s\n", SLI_QNAME[q->type]);
			} else {
				res = (void *)((uint8_t *)sli4->bmbx.virt +
						offsetof(sli4_cmd_sli_config_t, payload));

				if (res->status) {
					ocs_log_err(sli4->os, "bad destroy %s status=%#x addl=%#x\n",
							SLI_QNAME[q->type],
							res->status, res->additional_status);
				} else {
					rc = 0;
				}
			}
		}
	}

	if (free_memory) {
		ocs_lock_free(&q->lock);

		if (ocs_dma_free(sli4->os, &q->dma)) {
			ocs_log_err(sli4->os, "%s queue ID %d free failed\n",
				    SLI_QNAME[q->type], q->id);
			rc = -1;
		}
	}

	return rc;
}