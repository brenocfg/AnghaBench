#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {TYPE_1__* extent; } ;
struct TYPE_9__ {TYPE_2__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_3__ sli4_t ;
typedef  int int32_t ;
struct TYPE_7__ {int /*<<< orphan*/ * base; int /*<<< orphan*/ * use_map; } ;

/* Variables and functions */
 int SLI_RSRC_MAX ; 
 int /*<<< orphan*/  ocs_bitmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sli_fw_init (TYPE_3__*) ; 
 scalar_t__ sli_get_config (TYPE_3__*) ; 

int32_t
sli_reset(sli4_t *sli4)
{
	uint32_t	i;

	if (sli_fw_init(sli4)) {
		ocs_log_crit(sli4->os, "FW initialization failed\n");
		return -1;
	}

	if (sli4->config.extent[0].base) {
		ocs_free(sli4->os, sli4->config.extent[0].base, SLI_RSRC_MAX * sizeof(uint32_t));
		sli4->config.extent[0].base = NULL;
	}

	for (i = 0; i < SLI_RSRC_MAX; i++) {
		if (sli4->config.extent[i].use_map) {
			ocs_bitmap_free(sli4->config.extent[i].use_map);
			sli4->config.extent[i].use_map = NULL;
		}
		sli4->config.extent[i].base = NULL;
	}

	if (sli_get_config(sli4)) {
		return -1;
	}

	return 0;
}