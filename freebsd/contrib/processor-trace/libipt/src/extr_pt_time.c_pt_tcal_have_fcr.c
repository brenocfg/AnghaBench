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
struct pt_time_cal {scalar_t__ min_fcr; scalar_t__ max_fcr; } ;

/* Variables and functions */

__attribute__((used)) static int pt_tcal_have_fcr(const struct pt_time_cal *tcal)
{
	if (!tcal)
		return 0;

	return (tcal->min_fcr <= tcal->max_fcr);
}