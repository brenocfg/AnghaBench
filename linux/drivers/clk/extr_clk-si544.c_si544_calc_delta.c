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
typedef  int s64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int DELTA_M_MAX ; 
 scalar_t__ div_s64 (int,scalar_t__) ; 

__attribute__((used)) static s32 si544_calc_delta(s32 delta, s32 max_delta)
{
	s64 n = (s64)delta * DELTA_M_MAX;

	return div_s64(n, max_delta);
}