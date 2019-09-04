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
 int re_search_stub (struct re_pattern_buffer*,char const*,int,int,int /*<<< orphan*/ ,int,struct re_registers*,int) ; 

int
re_match (struct re_pattern_buffer *bufp,
	  const char *string,
	  int length,
	  int start,
	  struct re_registers *regs)
{
  return re_search_stub (bufp, string, length, start, 0, length, regs, 1);
}