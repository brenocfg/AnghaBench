#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;

/* Variables and functions */
 scalar_t__ CTRL_SIS_MODE ; 
 int /*<<< orphan*/  DBG_INIT (char*) ; 
 scalar_t__ PQI_GET_CTRL_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQI_SAVE_CTRL_MODE (int /*<<< orphan*/ *,scalar_t__) ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 scalar_t__ SIS_IS_KERNEL_PANIC (int /*<<< orphan*/ *) ; 
 scalar_t__ SIS_IS_KERNEL_UP (int /*<<< orphan*/ *) ; 
 int pqi_reset (int /*<<< orphan*/ *) ; 
 int pqisrc_reenable_sis (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sis_disable_interrupt (int /*<<< orphan*/ *) ; 

int pqisrc_force_sis(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;

	if (SIS_IS_KERNEL_PANIC(softs)) {
		DBG_INIT("Controller FW is not runnning");
		return PQI_STATUS_FAILURE;
	}

	if (PQI_GET_CTRL_MODE(softs) == CTRL_SIS_MODE) {
		return ret;
	}

	if (SIS_IS_KERNEL_UP(softs)) {
		PQI_SAVE_CTRL_MODE(softs, CTRL_SIS_MODE);
		return ret;
	}
	/* Disable interrupts ? */
	sis_disable_interrupt(softs);

	/* reset pqi, this will delete queues */
	ret = pqi_reset(softs);
	if (ret) {
		return ret;
	}	
	/* Re enable SIS */
	ret = pqisrc_reenable_sis(softs);
	if (ret) {
		return ret;
	}

	PQI_SAVE_CTRL_MODE(softs, CTRL_SIS_MODE);

	return ret;	
}