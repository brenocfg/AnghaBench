#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  r_idx; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  dma; TYPE_1__ u; int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ sli4_queue_t ;
struct TYPE_7__ {int vld; } ;
typedef  TYPE_3__ sli4_eqe_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  OCS_DMASYNC_PREWRITE ; 
#define  SLI_QTYPE_CQ 131 
#define  SLI_QTYPE_EQ 130 
#define  SLI_QTYPE_MQ 129 
#define  SLI_QTYPE_RQ 128 
 int TRUE ; 
 int /*<<< orphan*/  ocs_dma_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static uint8_t
sli_queue_entry_is_valid(sli4_queue_t *q, uint8_t *qe, uint8_t clear)
{
	uint8_t		valid = FALSE;

	switch (q->type) {
	case SLI_QTYPE_EQ:
		valid = ((sli4_eqe_t *)qe)->vld;
		if (valid && clear) {
			((sli4_eqe_t *)qe)->vld = 0;
		}
		break;
	case SLI_QTYPE_CQ:
		/*
		 * For both MCQE and WCQE/RCQE, the valid bit
		 * is bit 31 of dword 3 (0 based)
		 */
		valid = (qe[15] & 0x80) != 0;
		if (valid & clear) {
			qe[15] &= ~0x80;
		}
		break;
	case SLI_QTYPE_MQ:
		valid = q->index != q->u.r_idx;
		break;
	case SLI_QTYPE_RQ:
		valid = TRUE;
		clear = FALSE;
		break;
	default:
		ocs_log_test(NULL, "doesn't handle type=%#x\n", q->type);
	}

	if (clear) {
		ocs_dma_sync(&q->dma, OCS_DMASYNC_PREWRITE);
	}

	return valid;
}