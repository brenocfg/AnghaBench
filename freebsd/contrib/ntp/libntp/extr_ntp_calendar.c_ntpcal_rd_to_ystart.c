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
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {scalar_t__ lo; } ;

/* Variables and functions */
 TYPE_1__ ntpcal_split_eradays (scalar_t__,int /*<<< orphan*/ *) ; 

int32_t
ntpcal_rd_to_ystart(
	int32_t rd
	)
{
	/*
	 * Rather simple exercise: split the day number into elapsed
	 * years and elapsed days, then remove the elapsed days from the
	 * input value. Nice'n sweet...
	 */
	return rd - ntpcal_split_eradays(rd - 1, NULL).lo;
}