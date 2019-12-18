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
struct kinfo_proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * FIRST_THREAD_IN_PROC (struct proc*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_kinfo_aggregate (struct proc*,struct kinfo_proc*) ; 
 int /*<<< orphan*/  fill_kinfo_proc_only (struct proc*,struct kinfo_proc*) ; 
 int /*<<< orphan*/  fill_kinfo_thread (int /*<<< orphan*/ *,struct kinfo_proc*,int /*<<< orphan*/ ) ; 

void
fill_kinfo_proc(struct proc *p, struct kinfo_proc *kp)
{

	MPASS(FIRST_THREAD_IN_PROC(p) != NULL);

	fill_kinfo_proc_only(p, kp);
	fill_kinfo_thread(FIRST_THREAD_IN_PROC(p), kp, 0);
	fill_kinfo_aggregate(p, kp);
}