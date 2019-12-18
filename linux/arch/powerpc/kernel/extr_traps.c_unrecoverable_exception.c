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
struct pt_regs {int /*<<< orphan*/  msr; int /*<<< orphan*/  nip; int /*<<< orphan*/  trap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  die (char*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_emerg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void unrecoverable_exception(struct pt_regs *regs)
{
	pr_emerg("Unrecoverable exception %lx at %lx (msr=%lx)\n",
		 regs->trap, regs->nip, regs->msr);
	die("Unrecoverable exception", regs, SIGABRT);
}