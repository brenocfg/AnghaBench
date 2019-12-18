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
struct pt_regs {int /*<<< orphan*/  pstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SPSR_SS ; 

__attribute__((used)) static void set_regs_spsr_ss(struct pt_regs *regs)
{
	regs->pstate |= DBG_SPSR_SS;
}