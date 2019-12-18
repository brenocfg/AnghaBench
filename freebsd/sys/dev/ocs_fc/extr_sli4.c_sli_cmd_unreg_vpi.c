#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_3__ {int /*<<< orphan*/  command; } ;
struct TYPE_4__ {void* ii; int /*<<< orphan*/  index; TYPE_1__ hdr; } ;
typedef  TYPE_2__ sli4_cmd_unreg_vpi_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_UNREG_VPI ; 
#define  SLI4_UNREG_TYPE_ALL 131 
#define  SLI4_UNREG_TYPE_DOMAIN 130 
#define  SLI4_UNREG_TYPE_FCF 129 
#define  SLI4_UNREG_TYPE_PORT 128 
 void* SLI4_UNREG_VPI_II_FCFI ; 
 void* SLI4_UNREG_VPI_II_VFI ; 
 void* SLI4_UNREG_VPI_II_VPI ; 
 int /*<<< orphan*/  UINT16_MAX ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_unreg_vpi(sli4_t *sli4, void *buf, size_t size, uint16_t indicator, uint32_t which)
{
	sli4_cmd_unreg_vpi_t	*unreg_vpi = buf;

	if (!sli4 || !buf) {
		return 0;
	}

	ocs_memset(buf, 0, size);

	unreg_vpi->hdr.command = SLI4_MBOX_COMMAND_UNREG_VPI;
	unreg_vpi->index = indicator;
	switch (which) {
	case SLI4_UNREG_TYPE_PORT:
		unreg_vpi->ii = SLI4_UNREG_VPI_II_VPI;
		break;
	case SLI4_UNREG_TYPE_DOMAIN:
		unreg_vpi->ii = SLI4_UNREG_VPI_II_VFI;
		break;
	case SLI4_UNREG_TYPE_FCF:
		unreg_vpi->ii = SLI4_UNREG_VPI_II_FCFI;
		break;
	case SLI4_UNREG_TYPE_ALL:
		unreg_vpi->index = UINT16_MAX;	/* override indicator */
		unreg_vpi->ii = SLI4_UNREG_VPI_II_FCFI;
		break;
	default:
		return 0;
	}

	return sizeof(sli4_cmd_unreg_vpi_t);
}