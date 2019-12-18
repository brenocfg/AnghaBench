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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int sli4_resource_e ;
struct TYPE_5__ {int /*<<< orphan*/  command; } ;
struct TYPE_7__ {int destination_n_port_id; int /*<<< orphan*/  index; int /*<<< orphan*/  ii; int /*<<< orphan*/  dp; TYPE_1__ hdr; } ;
typedef  TYPE_3__ sli4_cmd_unreg_rpi_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_UNREG_RPI ; 
 int /*<<< orphan*/  SLI4_UNREG_RPI_II_FCFI ; 
 int /*<<< orphan*/  SLI4_UNREG_RPI_II_RPI ; 
 int /*<<< orphan*/  SLI4_UNREG_RPI_II_VFI ; 
 int /*<<< orphan*/  SLI4_UNREG_RPI_II_VPI ; 
#define  SLI_RSRC_FCOE_FCFI 131 
#define  SLI_RSRC_FCOE_RPI 130 
#define  SLI_RSRC_FCOE_VFI 129 
#define  SLI_RSRC_FCOE_VPI 128 
 int /*<<< orphan*/  TRUE ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_unreg_rpi(sli4_t *sli4, void *buf, size_t size, uint16_t indicator, sli4_resource_e which,
		uint32_t fc_id)
{
	sli4_cmd_unreg_rpi_t	*unreg_rpi = buf;
	uint8_t		index_indicator = 0;

	if (!sli4 || !buf) {
		return 0;
	}

	ocs_memset(buf, 0, size);

	unreg_rpi->hdr.command = SLI4_MBOX_COMMAND_UNREG_RPI;

	switch (which) {
	case SLI_RSRC_FCOE_RPI:
		index_indicator = SLI4_UNREG_RPI_II_RPI;
		if (fc_id != UINT32_MAX) {
			unreg_rpi->dp = TRUE;
			unreg_rpi->destination_n_port_id = fc_id & 0x00ffffff;
		}
		break;
	case SLI_RSRC_FCOE_VPI:
		index_indicator = SLI4_UNREG_RPI_II_VPI;
		break;
	case SLI_RSRC_FCOE_VFI:
		index_indicator = SLI4_UNREG_RPI_II_VFI;
		break;
	case SLI_RSRC_FCOE_FCFI:
		index_indicator = SLI4_UNREG_RPI_II_FCFI;
		break;
	default:
		ocs_log_test(sli4->os, "unknown type %#x\n", which);
		return 0;
	}

	unreg_rpi->ii = index_indicator;
	unreg_rpi->index = indicator;

	return sizeof(sli4_cmd_unreg_rpi_t);
}