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
struct TYPE_7__ {TYPE_2__ config; } ;
typedef  TYPE_3__ sli4_t ;
typedef  int sli4_resource_e ;
typedef  int int32_t ;
struct TYPE_5__ {size_t* base; size_t size; size_t number; int /*<<< orphan*/  use_map; } ;

/* Variables and functions */
#define  SLI_RSRC_FCOE_RPI 131 
#define  SLI_RSRC_FCOE_VFI 130 
#define  SLI_RSRC_FCOE_VPI 129 
#define  SLI_RSRC_FCOE_XRI 128 
 int /*<<< orphan*/  ocs_bitmap_clear (int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_resource_free(sli4_t *sli4, sli4_resource_e rtype, uint32_t rid)
{
	int32_t		rc = -1;
	uint32_t	x;
	uint32_t	size, *base;

	switch (rtype) {
	case SLI_RSRC_FCOE_VFI:
	case SLI_RSRC_FCOE_VPI:
	case SLI_RSRC_FCOE_RPI:
	case SLI_RSRC_FCOE_XRI:
		/*
		 * Figure out which extent contains the resource ID. I.e. find
		 * the extent such that
		 *   extent->base <= resource ID < extent->base + extent->size
		 */
		base = sli4->config.extent[rtype].base;
		size = sli4->config.extent[rtype].size;

		/*
		 * In the case of FW reset, this may be cleared but the force_free path will
		 * still attempt to free the resource. Prevent a NULL pointer access.
		 */
		if (base != NULL) {
			for (x = 0; x < sli4->config.extent[rtype].number; x++) {
				if ((rid >= base[x]) && (rid < (base[x] + size))) {
					rid -= base[x];
					ocs_bitmap_clear(sli4->config.extent[rtype].use_map,
							 (x * size) + rid);
					rc = 0;
					break;
				}
			}
		}
		break;
	default:
		;
	}

	return rc;
}