#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sf_size; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ FLASH_CFG_MAX_SIZE ; 
 scalar_t__ FLASH_CFG_START ; 

int t4_flash_cfg_addr(struct adapter *adapter)
{
	/*
	 * If the device FLASH isn't large enough to hold a Firmware
	 * Configuration File, return an error.
	 */
	if (adapter->params.sf_size < FLASH_CFG_START + FLASH_CFG_MAX_SIZE)
		return -ENOSPC;

	return FLASH_CFG_START;
}