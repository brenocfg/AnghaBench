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
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ ee_version; } ;
typedef  TYPE_1__ HAL_EEPROM ;

/* Variables and functions */
 scalar_t__ AR_EEPROM_VER3_2 ; 
 int NUM_INTERCEPTS ; 

__attribute__((used)) static void
getPcdacInterceptsFromPcdacMinMax(HAL_EEPROM *ee,
	uint16_t pcdacMin, uint16_t pcdacMax, uint16_t *vp)
{
	static const uint16_t intercepts3[] =
		{ 0, 5, 10, 20, 30, 50, 70, 85, 90, 95, 100 };
	static const uint16_t intercepts3_2[] =
		{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
	const uint16_t *ip = ee->ee_version < AR_EEPROM_VER3_2 ?
		intercepts3 : intercepts3_2;
	int i;

	/* loop for the percentages in steps or 5 */
	for (i = 0; i < NUM_INTERCEPTS; i++ )
		*vp++ = (ip[i] * pcdacMax + (100 - ip[i]) * pcdacMin) / 100;
}