#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__* extent; scalar_t__ has_extents; } ;
struct TYPE_10__ {int /*<<< orphan*/  bmbx; int /*<<< orphan*/  os; TYPE_3__ vpd; TYPE_2__ config; } ;
typedef  TYPE_4__ sli4_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {int /*<<< orphan*/ * use_map; int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 int SLI_RSRC_MAX ; 
 int /*<<< orphan*/  ocs_bitmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sli_fw_term (TYPE_4__*) ; 

int32_t
sli_teardown(sli4_t *sli4)
{
	uint32_t i;

	if (sli4->config.extent[0].base) {
		ocs_free(sli4->os, sli4->config.extent[0].base, SLI_RSRC_MAX * sizeof(uint32_t));
		sli4->config.extent[0].base = NULL;
	}

	for (i = 0; i < SLI_RSRC_MAX; i++) {
		if (sli4->config.has_extents) {
			/* TODO COMMON_DEALLOC_RESOURCE_EXTENTS */;
		}

		sli4->config.extent[i].base = NULL;

		ocs_bitmap_free(sli4->config.extent[i].use_map);
		sli4->config.extent[i].use_map = NULL;
	}

	if (sli_fw_term(sli4)) {
		ocs_log_err(sli4->os, "FW deinitialization failed\n");
	}

	ocs_dma_free(sli4->os, &sli4->vpd.data);
	ocs_dma_free(sli4->os, &sli4->bmbx);

	return 0;
}