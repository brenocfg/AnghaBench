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
 int ELINK_EEE_MODE_NVRAM_AGGRESSIVE_TIME ; 
 int ELINK_EEE_MODE_NVRAM_BALANCED_TIME ; 
 int ELINK_EEE_MODE_NVRAM_LATENCY_TIME ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
#define  PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE 130 
#define  PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED 129 
#define  PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY 128 

__attribute__((used)) static elink_status_t elink_eee_nvram_to_time(uint32_t nvram_mode, uint32_t *idle_timer)
{
	switch (nvram_mode) {
	case PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED:
		*idle_timer = ELINK_EEE_MODE_NVRAM_BALANCED_TIME;
		break;
	case PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE:
		*idle_timer = ELINK_EEE_MODE_NVRAM_AGGRESSIVE_TIME;
		break;
	case PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY:
		*idle_timer = ELINK_EEE_MODE_NVRAM_LATENCY_TIME;
		break;
	default:
		*idle_timer = 0;
		break;
	}

	return ELINK_STATUS_OK;
}