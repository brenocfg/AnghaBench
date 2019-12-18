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
struct pt_regs {int estatus; unsigned long ea; unsigned long sp; } ;

/* Variables and functions */
 int ESTATUS_EPIE ; 
 int ESTATUS_EU ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void start_thread(struct pt_regs *regs, unsigned long pc, unsigned long sp)
{
	memset((void *) regs, 0, sizeof(struct pt_regs));
	regs->estatus = ESTATUS_EPIE | ESTATUS_EU;
	regs->ea = pc;
	regs->sp = sp;
}