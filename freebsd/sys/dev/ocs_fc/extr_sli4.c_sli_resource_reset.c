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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {TYPE_1__* extent; } ;
struct TYPE_7__ {TYPE_2__ config; } ;
typedef  TYPE_3__ sli4_t ;
typedef  int sli4_resource_e ;
typedef  int int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  use_map; int /*<<< orphan*/  map_size; } ;

/* Variables and functions */
#define  SLI_RSRC_FCOE_RPI 131 
#define  SLI_RSRC_FCOE_VFI 130 
#define  SLI_RSRC_FCOE_VPI 129 
#define  SLI_RSRC_FCOE_XRI 128 
 int /*<<< orphan*/  ocs_bitmap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t
sli_resource_reset(sli4_t *sli4, sli4_resource_e rtype)
{
	int32_t		rc = -1;
	uint32_t	i;

	switch (rtype) {
	case SLI_RSRC_FCOE_VFI:
	case SLI_RSRC_FCOE_VPI:
	case SLI_RSRC_FCOE_RPI:
	case SLI_RSRC_FCOE_XRI:
		for (i = 0; i < sli4->config.extent[rtype].map_size; i++) {
			ocs_bitmap_clear(sli4->config.extent[rtype].use_map, i);
		}
		rc = 0;
		break;
	default:
		;
	}

	return rc;
}