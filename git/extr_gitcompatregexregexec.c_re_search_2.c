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
struct re_registers {int dummy; } ;
struct re_pattern_buffer {int dummy; } ;

/* Variables and functions */
 int re_search_2_stub (struct re_pattern_buffer*,char const*,int,char const*,int,int,int,struct re_registers*,int,int /*<<< orphan*/ ) ; 

int
re_search_2 (struct re_pattern_buffer *bufp,
	     const char *string1, int length1,
	     const char *string2, int length2, int start,
	     int range, struct re_registers *regs,  int stop)
{
  return re_search_2_stub (bufp, string1, length1, string2, length2,
			   start, range, regs, stop, 0);
}