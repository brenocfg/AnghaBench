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
struct proc {int /*<<< orphan*/  p_xsig; } ;

/* Variables and functions */
 int /*<<< orphan*/  childproc_jobstate (struct proc*,int,int /*<<< orphan*/ ) ; 

void
childproc_stopped(struct proc *p, int reason)
{

	childproc_jobstate(p, reason, p->p_xsig);
}