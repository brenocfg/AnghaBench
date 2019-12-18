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
typedef  int uint32_t ;
struct elink_vars {int eee_status; } ;
struct elink_params {int port; int eee_mode; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int ELINK_EEE_MODE_ENABLE_LPI ; 
 int ELINK_EEE_MODE_OUTPUT_TIME ; 
 int ELINK_EEE_MODE_OVERRIDE_NVRAM ; 
 int /*<<< orphan*/  ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 scalar_t__ MISC_REG_CPMU_LP_IDLE_THR_P0 ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 int SHMEM_EEE_TIMER_MASK ; 
 int SHMEM_EEE_TIME_OUTPUT_BIT ; 
 int elink_eee_calc_timer (struct elink_params*) ; 
 scalar_t__ elink_eee_time_to_nvram (int,int*) ; 

__attribute__((used)) static elink_status_t elink_eee_set_timers(struct elink_params *params,
				   struct elink_vars *vars)
{
	uint32_t eee_idle = 0, eee_mode;
	struct bxe_softc *sc = params->sc;

	eee_idle = elink_eee_calc_timer(params);

	if (eee_idle) {
		REG_WR(sc, MISC_REG_CPMU_LP_IDLE_THR_P0 + (params->port << 2),
		       eee_idle);
	} else if ((params->eee_mode & ELINK_EEE_MODE_ENABLE_LPI) &&
		   (params->eee_mode & ELINK_EEE_MODE_OVERRIDE_NVRAM) &&
		   (params->eee_mode & ELINK_EEE_MODE_OUTPUT_TIME)) {
		ELINK_DEBUG_P0(sc, "Error: Tx LPI is enabled with timer 0\n");
		return ELINK_STATUS_ERROR;
	}

	vars->eee_status &= ~(SHMEM_EEE_TIMER_MASK | SHMEM_EEE_TIME_OUTPUT_BIT);
	if (params->eee_mode & ELINK_EEE_MODE_OUTPUT_TIME) {
		/* eee_idle in 1u --> eee_status in 16u */
		eee_idle >>= 4;
		vars->eee_status |= (eee_idle & SHMEM_EEE_TIMER_MASK) |
				    SHMEM_EEE_TIME_OUTPUT_BIT;
	} else {
		if (elink_eee_time_to_nvram(eee_idle, &eee_mode))
			return ELINK_STATUS_ERROR;
		vars->eee_status |= eee_mode;
	}

	return ELINK_STATUS_OK;
}