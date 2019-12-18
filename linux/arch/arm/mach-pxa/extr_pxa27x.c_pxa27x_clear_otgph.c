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

/* Variables and functions */
 int PSSR ; 
 int PSSR_OTGPH ; 
 scalar_t__ cpu_is_pxa27x () ; 

void pxa27x_clear_otgph(void)
{
	if (cpu_is_pxa27x() && (PSSR & PSSR_OTGPH))
		PSSR |= PSSR_OTGPH;
}