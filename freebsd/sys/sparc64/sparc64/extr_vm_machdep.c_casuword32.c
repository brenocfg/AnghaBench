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
 int casuword32_int (int volatile*,int,int) ; 

uint32_t
casuword32(volatile uint32_t *base, uint32_t oldval, uint32_t newval)
{
	uint32_t ret;

	ret = casuword32_int(base, oldval, newval);
	if (ret != -1)
		ret = ret != oldval;
	return (ret);
}