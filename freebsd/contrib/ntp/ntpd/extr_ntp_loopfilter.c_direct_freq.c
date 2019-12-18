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
 double clock_epoch ; 
 double current_time ; 
 double drift_comp ; 
 int /*<<< orphan*/  set_freq (double) ; 

__attribute__((used)) static double
direct_freq(
	double	fp_offset
	)
{
	set_freq(fp_offset / (current_time - clock_epoch));

	return drift_comp;
}