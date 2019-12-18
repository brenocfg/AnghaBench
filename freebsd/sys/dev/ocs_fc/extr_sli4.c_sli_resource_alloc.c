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
typedef  size_t uint32_t ;
struct TYPE_6__ {TYPE_1__* extent; } ;
struct TYPE_7__ {TYPE_2__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_3__ sli4_t ;
typedef  int sli4_resource_e ;
typedef  int int32_t ;
struct TYPE_5__ {size_t size; size_t* base; int /*<<< orphan*/  n_alloc; int /*<<< orphan*/  map_size; int /*<<< orphan*/  use_map; } ;

/* Variables and functions */
#define  SLI_RSRC_FCOE_RPI 131 
#define  SLI_RSRC_FCOE_VFI 130 
#define  SLI_RSRC_FCOE_VPI 129 
#define  SLI_RSRC_FCOE_XRI 128 
 size_t UINT32_MAX ; 
 int ocs_bitmap_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

int32_t
sli_resource_alloc(sli4_t *sli4, sli4_resource_e rtype, uint32_t *rid, uint32_t *index)
{
	int32_t		rc = 0;
	uint32_t	size;
	uint32_t	extent_idx;
	uint32_t	item_idx;
	int		status;

	*rid = UINT32_MAX;
	*index = UINT32_MAX;

	switch (rtype) {
	case SLI_RSRC_FCOE_VFI:
	case SLI_RSRC_FCOE_VPI:
	case SLI_RSRC_FCOE_RPI:
	case SLI_RSRC_FCOE_XRI:
		status = ocs_bitmap_find(sli4->config.extent[rtype].use_map,
				sli4->config.extent[rtype].map_size);
		if (status < 0) {
			ocs_log_err(sli4->os, "out of resource %d (alloc=%d)\n",
					rtype, sli4->config.extent[rtype].n_alloc);
			rc = -1;
			break;
		} else {
			*index = status;
		}

		size = sli4->config.extent[rtype].size;

		extent_idx = *index / size;
		item_idx   = *index % size;

		*rid = sli4->config.extent[rtype].base[extent_idx] + item_idx;

		sli4->config.extent[rtype].n_alloc++;
		break;
	default:
		rc = -1;
	}

	return rc;
}