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
typedef  int bug_insn_t ;

/* Variables and functions */
 int __INSN_LENGTH_32 ; 
 int __INSN_LENGTH_MASK ; 
 scalar_t__ probe_kernel_address (int*,int) ; 

__attribute__((used)) static inline unsigned long get_break_insn_length(unsigned long pc)
{
	bug_insn_t insn;

	if (probe_kernel_address((bug_insn_t *)pc, insn))
		return 0;
	return (((insn & __INSN_LENGTH_MASK) == __INSN_LENGTH_32) ? 4UL : 2UL);
}