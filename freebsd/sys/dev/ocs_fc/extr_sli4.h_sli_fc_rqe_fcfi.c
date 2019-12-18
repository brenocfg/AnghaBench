#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_4__ {int fcfi; } ;
typedef  TYPE_1__ sli4_fc_optimized_write_cmd_cqe_t ;
struct TYPE_5__ {int fcfi; } ;
typedef  TYPE_2__ sli4_fc_async_rcqe_v1_t ;
struct TYPE_6__ {int fcfi; } ;
typedef  TYPE_3__ sli4_fc_async_rcqe_t ;

/* Variables and functions */
 size_t SLI4_CQE_CODE_OFFSET ; 
#define  SLI4_CQE_CODE_OPTIMIZED_WRITE_CMD 130 
#define  SLI4_CQE_CODE_RQ_ASYNC 129 
#define  SLI4_CQE_CODE_RQ_ASYNC_V1 128 
 int UINT8_MAX ; 

__attribute__((used)) static inline uint8_t
sli_fc_rqe_fcfi(sli4_t *sli4, void *cqe)
{
	uint8_t code = ((uint8_t*)cqe)[SLI4_CQE_CODE_OFFSET];
	uint8_t fcfi = UINT8_MAX;

	switch(code) {
	case SLI4_CQE_CODE_RQ_ASYNC: {
		sli4_fc_async_rcqe_t *rcqe = cqe;
		fcfi = rcqe->fcfi;
		break;
	}
	case SLI4_CQE_CODE_RQ_ASYNC_V1: {
		sli4_fc_async_rcqe_v1_t *rcqev1 = cqe;
		fcfi = rcqev1->fcfi;
		break;
	}
	case SLI4_CQE_CODE_OPTIMIZED_WRITE_CMD: {
		sli4_fc_optimized_write_cmd_cqe_t *opt_wr = cqe;
		fcfi = opt_wr->fcfi;
		break;
	}
	}

	return fcfi;
}