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
typedef  scalar_t__ LINENUM ;

/* Variables and functions */
 scalar_t__ p_end ; 
 scalar_t__ p_first ; 
 scalar_t__ p_indent ; 
 scalar_t__ p_max ; 
 scalar_t__ p_newfirst ; 
 scalar_t__ p_ptrn_lines ; 
 scalar_t__ p_repl_lines ; 

void
re_patch(void)
{
	p_first = 0;
	p_newfirst = 0;
	p_ptrn_lines = 0;
	p_repl_lines = 0;
	p_end = (LINENUM) - 1;
	p_max = 0;
	p_indent = 0;
}