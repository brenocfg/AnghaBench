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

/* Variables and functions */
 int MMC_OCR_MAX_VOLTAGE_SHIFT ; 
 int MMC_OCR_MIN_VOLTAGE_SHIFT ; 

__attribute__((used)) static int
mmc_highest_voltage(uint32_t ocr)
{
	int i;

	for (i = MMC_OCR_MAX_VOLTAGE_SHIFT;
	    i >= MMC_OCR_MIN_VOLTAGE_SHIFT; i--)
		if (ocr & (1 << i))
			return (i);
	return (-1);
}