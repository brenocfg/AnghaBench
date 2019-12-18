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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned long instruction_pointer (struct pt_regs*) ; 
 unsigned long instruction_pointer_guest (struct pt_regs*) ; 
 scalar_t__ is_in_guest (struct pt_regs*) ; 

unsigned long perf_instruction_pointer(struct pt_regs *regs)
{
	return is_in_guest(regs) ? instruction_pointer_guest(regs)
				 : instruction_pointer(regs);
}