#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_5__ {int /*<<< orphan*/  check_ref_tag; } ;
typedef  TYPE_1__ ocs_hw_dif_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  ref_tag; } ;
typedef  TYPE_2__ ocs_dif_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ ocs_be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint32_t
ocs_scsi_dif_check_ref_tag(ocs_t *ocs, ocs_hw_dif_info_t *dif_info, uint32_t exp_ref_tag, ocs_dif_t *dif)
{
	if ((dif == NULL)  || !dif_info->check_ref_tag) {
		return TRUE;
	}

	if (exp_ref_tag != ocs_be32toh(dif->ref_tag)) {
		ocs_log_debug(ocs, "expected ref tag 0x%x, actual 0x%x\n",
			exp_ref_tag, ocs_be32toh(dif->ref_tag));
		return FALSE;
	} else {
		return TRUE;
	}
}