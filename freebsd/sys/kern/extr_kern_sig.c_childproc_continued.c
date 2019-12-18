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
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLD_CONTINUED ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  childproc_jobstate (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
childproc_continued(struct proc *p)
{
	childproc_jobstate(p, CLD_CONTINUED, SIGCONT);
}