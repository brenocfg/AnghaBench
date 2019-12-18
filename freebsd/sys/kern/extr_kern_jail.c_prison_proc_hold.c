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
struct prison {scalar_t__ pr_uref; int /*<<< orphan*/  pr_mtx; int /*<<< orphan*/  pr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
prison_proc_hold(struct prison *pr)
{

	mtx_lock(&pr->pr_mtx);
	KASSERT(pr->pr_uref > 0,
	    ("Cannot add a process to a non-alive prison (jid=%d)", pr->pr_id));
	pr->pr_uref++;
	mtx_unlock(&pr->pr_mtx);
}