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
typedef  int uint32_t ;
struct TYPE_5__ {int wqe_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  os; TYPE_1__ config; int /*<<< orphan*/  port_type; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 int SLI4_FCOE_RQE_SIZE ; 
 int /*<<< orphan*/  SLI4_PORT_TYPE_FC ; 
#define  SLI_QTYPE_CQ 132 
#define  SLI_QTYPE_EQ 131 
#define  SLI_QTYPE_MQ 130 
#define  SLI_QTYPE_RQ 129 
#define  SLI_QTYPE_WQ 128 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,...) ; 

int32_t
sli_get_queue_entry_size(sli4_t *sli4, uint32_t qtype)
{
	uint32_t	size = 0;

	if (!sli4) {
		ocs_log_err(NULL, "bad parameter sli4=%p\n", sli4);
		return -1;
	}

	switch (qtype) {
	case SLI_QTYPE_EQ:
		size = sizeof(uint32_t);
		break;
	case SLI_QTYPE_CQ:
		size = 16;
		break;
	case SLI_QTYPE_MQ:
		size = 256;
		break;
	case SLI_QTYPE_WQ:
		if (SLI4_PORT_TYPE_FC == sli4->port_type) {
			size = sli4->config.wqe_size;
		} else {
			/* TODO */
			ocs_log_test(sli4->os, "unsupported queue entry size\n");
			return -1;
		}
		break;
	case SLI_QTYPE_RQ:
		size = SLI4_FCOE_RQE_SIZE;
		break;
	default:
		ocs_log_test(sli4->os, "unknown queue type %d\n", qtype);
		return -1;
	}
	return size;
}