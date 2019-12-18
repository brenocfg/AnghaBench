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
struct ucred {int dummy; } ;
struct proc {int /*<<< orphan*/  p_ucred; } ;

/* Variables and functions */
 int seeotheruids_check (struct ucred*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
seeotheruids_proc_check_sched(struct ucred *cred, struct proc *p)
{

	return (seeotheruids_check(cred, p->p_ucred));
}