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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ ee_version; } ;
typedef  TYPE_1__ HAL_EEPROM ;

/* Variables and functions */
 scalar_t__ AR_EEPROM_VER3_2 ; 
 scalar_t__ CHANNEL_UNUSED ; 

__attribute__((used)) static uint16_t
fbin2freq_2p4(HAL_EEPROM *ee, uint16_t fbin)
{
	if (fbin == CHANNEL_UNUSED)	/* reserved value, don't convert */
		return fbin;
	return ee->ee_version <= AR_EEPROM_VER3_2 ?
		2400 + fbin :
		2300 + fbin;
}