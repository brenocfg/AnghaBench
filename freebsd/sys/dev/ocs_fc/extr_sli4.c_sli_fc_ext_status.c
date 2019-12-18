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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_2__ {int status; int wqe_specific_2; } ;
typedef  TYPE_1__ sli4_fc_wcqe_t ;

/* Variables and functions */
#define  SLI4_FC_WCQE_STATUS_CMD_REJECT 136 
#define  SLI4_FC_WCQE_STATUS_DI_ERROR 135 
#define  SLI4_FC_WCQE_STATUS_FABRIC_BSY 134 
#define  SLI4_FC_WCQE_STATUS_FABRIC_RJT 133 
#define  SLI4_FC_WCQE_STATUS_FCP_RSP_FAILURE 132 
#define  SLI4_FC_WCQE_STATUS_LOCAL_REJECT 131 
#define  SLI4_FC_WCQE_STATUS_LS_RJT 130 
#define  SLI4_FC_WCQE_STATUS_NPORT_BSY 129 
#define  SLI4_FC_WCQE_STATUS_NPORT_RJT 128 
 int UINT32_MAX ; 

uint32_t
sli_fc_ext_status(sli4_t *sli4, uint8_t *cqe)
{
	sli4_fc_wcqe_t *wcqe = (void *)cqe;
	uint32_t	mask;

	switch (wcqe->status) {
	case SLI4_FC_WCQE_STATUS_FCP_RSP_FAILURE:
		mask = UINT32_MAX;
		break;
	case SLI4_FC_WCQE_STATUS_LOCAL_REJECT:
	case SLI4_FC_WCQE_STATUS_CMD_REJECT:
		mask = 0xff;
		break;
	case SLI4_FC_WCQE_STATUS_NPORT_RJT:
	case SLI4_FC_WCQE_STATUS_FABRIC_RJT:
	case SLI4_FC_WCQE_STATUS_NPORT_BSY:
	case SLI4_FC_WCQE_STATUS_FABRIC_BSY:
	case SLI4_FC_WCQE_STATUS_LS_RJT:
		mask = UINT32_MAX;
		break;
	case SLI4_FC_WCQE_STATUS_DI_ERROR:
		mask = UINT32_MAX;
		break;
	default:
		mask = 0;
	}

	return wcqe->wqe_specific_2 & mask;
}