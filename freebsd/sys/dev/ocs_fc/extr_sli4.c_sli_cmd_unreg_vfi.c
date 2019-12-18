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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_5__ {int /*<<< orphan*/  command; } ;
struct TYPE_6__ {int /*<<< orphan*/  ii; int /*<<< orphan*/  index; TYPE_1__ hdr; } ;
typedef  TYPE_2__ sli4_cmd_unreg_vfi_t ;
struct TYPE_7__ {int /*<<< orphan*/  fcf_indicator; int /*<<< orphan*/  indicator; } ;
typedef  TYPE_3__ ocs_domain_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_UNREG_VFI ; 
#define  SLI4_UNREG_TYPE_ALL 130 
#define  SLI4_UNREG_TYPE_DOMAIN 129 
#define  SLI4_UNREG_TYPE_FCF 128 
 int /*<<< orphan*/  SLI4_UNREG_VFI_II_FCFI ; 
 int /*<<< orphan*/  UINT16_MAX ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_unreg_vfi(sli4_t *sli4, void *buf, size_t size, ocs_domain_t *domain, uint32_t which)
{
	sli4_cmd_unreg_vfi_t	*unreg_vfi = buf;

	if (!sli4 || !buf || !domain) {
		return 0;
	}

	ocs_memset(buf, 0, size);

	unreg_vfi->hdr.command = SLI4_MBOX_COMMAND_UNREG_VFI;
	switch (which) {
	case SLI4_UNREG_TYPE_DOMAIN:
		unreg_vfi->index = domain->indicator;
		break;
	case SLI4_UNREG_TYPE_FCF:
		unreg_vfi->index = domain->fcf_indicator;
		break;
	case SLI4_UNREG_TYPE_ALL:
		unreg_vfi->index = UINT16_MAX;
		break;
	default:
		return 0;
	}

	if (SLI4_UNREG_TYPE_DOMAIN != which) {
		unreg_vfi->ii = SLI4_UNREG_VFI_II_FCFI;
	}

	return sizeof(sli4_cmd_unreg_vfi_t);
}