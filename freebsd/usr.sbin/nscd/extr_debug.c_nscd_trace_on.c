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
 scalar_t__ trace_level ; 
 scalar_t__ trace_level_bk ; 

void
nscd_trace_on(void)
{
	trace_level = trace_level_bk;
	trace_level_bk = 0;
}