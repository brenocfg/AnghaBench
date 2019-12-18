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
struct p_times {scalar_t__ pt_pctcpu; } ;

/* Variables and functions */

int
compar(const void *a, const void *b)
{
	return (((const struct p_times *) a)->pt_pctcpu >
		((const struct p_times *) b)->pt_pctcpu)? -1: 1;
}