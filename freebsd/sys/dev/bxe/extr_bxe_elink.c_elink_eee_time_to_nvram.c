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
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
#define  ELINK_EEE_MODE_NVRAM_AGGRESSIVE_TIME 130 
#define  ELINK_EEE_MODE_NVRAM_BALANCED_TIME 129 
#define  ELINK_EEE_MODE_NVRAM_LATENCY_TIME 128 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE ; 
 int PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED ; 
 int PORT_FEAT_CFG_EEE_POWER_MODE_DISABLED ; 
 int PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY ; 

__attribute__((used)) static elink_status_t elink_eee_time_to_nvram(uint32_t idle_timer, uint32_t *nvram_mode)
{
	switch (idle_timer) {
	case ELINK_EEE_MODE_NVRAM_BALANCED_TIME:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED;
		break;
	case ELINK_EEE_MODE_NVRAM_AGGRESSIVE_TIME:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE;
		break;
	case ELINK_EEE_MODE_NVRAM_LATENCY_TIME:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY;
		break;
	default:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_DISABLED;
		break;
	}

	return ELINK_STATUS_OK;
}