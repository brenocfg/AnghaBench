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
struct rlimit {int /*<<< orphan*/  rlim_cur; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  rlim_t ;

/* Variables and functions */
 int /*<<< orphan*/  lim_rlimit_proc (struct proc*,int,struct rlimit*) ; 

rlim_t
lim_cur_proc(struct proc *p, int which)
{
	struct rlimit rl;

	lim_rlimit_proc(p, which, &rl);
	return (rl.rlim_cur);
}