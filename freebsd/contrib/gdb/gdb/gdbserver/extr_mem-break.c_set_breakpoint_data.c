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
 char const* breakpoint_data ; 
 int breakpoint_len ; 

void
set_breakpoint_data (const char *bp_data, int bp_len)
{
  breakpoint_data = bp_data;
  breakpoint_len = bp_len;
}