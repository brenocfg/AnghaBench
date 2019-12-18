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
 scalar_t__ machine_is_tosa () ; 
 int max1111_read_channel (int) ; 

int sharpsl_pm_pxa_read_max1111(int channel)
{
	/* Ugly, better move this function into another module */
	if (machine_is_tosa())
	    return 0;

	/* max1111 accepts channels from 0-3, however,
	 * it is encoded from 0-7 here in the code.
	 */
	return max1111_read_channel(channel >> 1);
}