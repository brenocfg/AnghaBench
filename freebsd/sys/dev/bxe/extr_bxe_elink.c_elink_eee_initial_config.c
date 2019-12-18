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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct elink_vars {int eee_status; } ;
struct elink_params {int eee_mode; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int ELINK_EEE_MODE_ADV_LPI ; 
 int ELINK_EEE_MODE_ENABLE_LPI ; 
 int SHMEM_EEE_LPI_REQUESTED_BIT ; 
 int SHMEM_EEE_REQUESTED_BIT ; 
 int SHMEM_EEE_SUPPORTED_SHIFT ; 
 int /*<<< orphan*/  elink_eee_set_timers (struct elink_params*,struct elink_vars*) ; 

__attribute__((used)) static elink_status_t elink_eee_initial_config(struct elink_params *params,
				     struct elink_vars *vars, uint8_t mode)
{
	vars->eee_status |= ((uint32_t) mode) << SHMEM_EEE_SUPPORTED_SHIFT;

	/* Propagate params' bits --> vars (for migration exposure) */
	if (params->eee_mode & ELINK_EEE_MODE_ENABLE_LPI)
		vars->eee_status |= SHMEM_EEE_LPI_REQUESTED_BIT;
	else
		vars->eee_status &= ~SHMEM_EEE_LPI_REQUESTED_BIT;

	if (params->eee_mode & ELINK_EEE_MODE_ADV_LPI)
		vars->eee_status |= SHMEM_EEE_REQUESTED_BIT;
	else
		vars->eee_status &= ~SHMEM_EEE_REQUESTED_BIT;

	return elink_eee_set_timers(params, vars);
}