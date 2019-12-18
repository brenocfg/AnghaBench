#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lo; } ;
typedef  TYPE_1__ ntpcal_split ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 TYPE_1__ ntpcal_split_eradays (scalar_t__,int*) ; 
 TYPE_1__ ntpcal_split_yeardays (scalar_t__,int) ; 

int32_t
ntpcal_rd_to_mstart(
	int32_t rd
	)
{
	ntpcal_split split;
	int	     leaps;

	split = ntpcal_split_eradays(rd - 1, &leaps);
	split = ntpcal_split_yeardays(split.lo, leaps);

	return rd - split.lo;
}