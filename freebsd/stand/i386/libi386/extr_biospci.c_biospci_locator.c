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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int int8_t ;

/* Variables and functions */

uint32_t
biospci_locator(int8_t bus, uint8_t device, uint8_t function)
{

	return ((bus << 8) | ((device & 0x1f) << 3) | (function & 0x7));
}