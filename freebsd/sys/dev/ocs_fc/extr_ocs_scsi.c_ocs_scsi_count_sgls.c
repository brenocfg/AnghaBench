#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ocs_scsi_sgl_t ;
struct TYPE_3__ {scalar_t__ dif_oper; scalar_t__ dif_separate; } ;
typedef  TYPE_1__ ocs_hw_dif_info_t ;

/* Variables and functions */
 scalar_t__ OCS_HW_DIF_OPER_DISABLED ; 

__attribute__((used)) static uint32_t
ocs_scsi_count_sgls(ocs_hw_dif_info_t *hw_dif, ocs_scsi_sgl_t *sgl, uint32_t sgl_count)
{
	uint32_t count = 0;
	uint32_t i;

	/* Convert DIF Information */
	if (hw_dif->dif_oper != OCS_HW_DIF_OPER_DISABLED) {

		/* If we're not DIF separate, then emit a seed SGE */
		if (!hw_dif->dif_separate) {
			count++;
		}

		for (i = 0; i < sgl_count; i++) {
			/* If DIF is enabled, and DIF is separate, then append a SEED then DIF SGE */
			if (hw_dif->dif_separate) {
				count += 2;
			}

			count++;
		}
	} else {
		count = sgl_count;
	}
	return count;
}