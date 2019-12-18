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
 unsigned int BRANCH_SET_LINK ; 
 scalar_t__ instr_is_relative_branch (unsigned int) ; 

int instr_is_relative_link_branch(unsigned int instr)
{
	return instr_is_relative_branch(instr) && (instr & BRANCH_SET_LINK);
}