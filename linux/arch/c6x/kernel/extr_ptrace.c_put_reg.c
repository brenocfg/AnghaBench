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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int PT_CSR ; 
 int PT_TSR ; 
 scalar_t__ task_pt_regs (struct task_struct*) ; 

__attribute__((used)) static inline int put_reg(struct task_struct *task,
			  int regno,
			  unsigned long data)
{
	unsigned long *addr = (unsigned long *)task_pt_regs(task);

	if (regno != PT_TSR && regno != PT_CSR)
		addr[regno] = data;

	return 0;
}