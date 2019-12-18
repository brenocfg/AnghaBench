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
struct dyn_ftrace {unsigned long ip; } ;

/* Variables and functions */
 unsigned char* ftrace_call_replace (unsigned long,unsigned long) ; 
 int ftrace_modify_code (unsigned long,unsigned char*,unsigned char*,int) ; 
 unsigned char* ftrace_nop_replace () ; 

int ftrace_make_call(struct dyn_ftrace *rec, unsigned long addr)
{
	unsigned long ip = rec->ip;
	unsigned char *old, *new;

	old=  ftrace_nop_replace();
	new = ftrace_call_replace(ip, addr);
	return ftrace_modify_code(ip, old, new, 1);
}