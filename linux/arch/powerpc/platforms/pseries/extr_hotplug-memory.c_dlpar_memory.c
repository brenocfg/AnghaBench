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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  index; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int /*<<< orphan*/  drc_index; TYPE_1__ ic; int /*<<< orphan*/  drc_count; } ;
struct pseries_hp_errorlog {int action; TYPE_2__ _drc_u; int /*<<< orphan*/  id_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PSERIES_HP_ELOG_ACTION_ADD 133 
#define  PSERIES_HP_ELOG_ACTION_READD 132 
#define  PSERIES_HP_ELOG_ACTION_REMOVE 131 
#define  PSERIES_HP_ELOG_ID_DRC_COUNT 130 
#define  PSERIES_HP_ELOG_ID_DRC_IC 129 
#define  PSERIES_HP_ELOG_ID_DRC_INDEX 128 
 int dlpar_memory_add_by_count (int /*<<< orphan*/ ) ; 
 int dlpar_memory_add_by_ic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dlpar_memory_add_by_index (int /*<<< orphan*/ ) ; 
 int dlpar_memory_readd_by_index (int /*<<< orphan*/ ) ; 
 int dlpar_memory_remove_by_count (int /*<<< orphan*/ ) ; 
 int dlpar_memory_remove_by_ic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dlpar_memory_remove_by_index (int /*<<< orphan*/ ) ; 
 int drmem_update_dt () ; 
 int /*<<< orphan*/  lock_device_hotplug () ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int rtas_hp_event ; 
 int /*<<< orphan*/  unlock_device_hotplug () ; 

int dlpar_memory(struct pseries_hp_errorlog *hp_elog)
{
	u32 count, drc_index;
	int rc;

	lock_device_hotplug();

	switch (hp_elog->action) {
	case PSERIES_HP_ELOG_ACTION_ADD:
		switch (hp_elog->id_type) {
		case PSERIES_HP_ELOG_ID_DRC_COUNT:
			count = hp_elog->_drc_u.drc_count;
			rc = dlpar_memory_add_by_count(count);
			break;
		case PSERIES_HP_ELOG_ID_DRC_INDEX:
			drc_index = hp_elog->_drc_u.drc_index;
			rc = dlpar_memory_add_by_index(drc_index);
			break;
		case PSERIES_HP_ELOG_ID_DRC_IC:
			count = hp_elog->_drc_u.ic.count;
			drc_index = hp_elog->_drc_u.ic.index;
			rc = dlpar_memory_add_by_ic(count, drc_index);
			break;
		default:
			rc = -EINVAL;
			break;
		}

		break;
	case PSERIES_HP_ELOG_ACTION_REMOVE:
		switch (hp_elog->id_type) {
		case PSERIES_HP_ELOG_ID_DRC_COUNT:
			count = hp_elog->_drc_u.drc_count;
			rc = dlpar_memory_remove_by_count(count);
			break;
		case PSERIES_HP_ELOG_ID_DRC_INDEX:
			drc_index = hp_elog->_drc_u.drc_index;
			rc = dlpar_memory_remove_by_index(drc_index);
			break;
		case PSERIES_HP_ELOG_ID_DRC_IC:
			count = hp_elog->_drc_u.ic.count;
			drc_index = hp_elog->_drc_u.ic.index;
			rc = dlpar_memory_remove_by_ic(count, drc_index);
			break;
		default:
			rc = -EINVAL;
			break;
		}

		break;
	case PSERIES_HP_ELOG_ACTION_READD:
		drc_index = hp_elog->_drc_u.drc_index;
		rc = dlpar_memory_readd_by_index(drc_index);
		break;
	default:
		pr_err("Invalid action (%d) specified\n", hp_elog->action);
		rc = -EINVAL;
		break;
	}

	if (!rc) {
		rtas_hp_event = true;
		rc = drmem_update_dt();
		rtas_hp_event = false;
	}

	unlock_device_hotplug();
	return rc;
}