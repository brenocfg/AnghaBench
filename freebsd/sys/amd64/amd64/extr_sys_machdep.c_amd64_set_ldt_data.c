#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct user_segment_descriptor {int dummy; } ;
struct thread {TYPE_1__* td_proc; } ;
struct proc_ldt {scalar_t__ ldt_base; } ;
struct mdproc {struct proc_ldt* md_ldt; } ;
struct TYPE_2__ {struct mdproc p_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  dt_lock ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
amd64_set_ldt_data(struct thread *td, int start, int num,
    struct user_segment_descriptor *descs)
{
	struct mdproc *mdp;
	struct proc_ldt *pldt;
	volatile uint64_t *dst, *src;
	int i;

	mtx_assert(&dt_lock, MA_OWNED);

	mdp = &td->td_proc->p_md;
	pldt = mdp->md_ldt;
	dst = (volatile uint64_t *)(pldt->ldt_base);
	src = (volatile uint64_t *)descs;
	for (i = 0; i < num; i++)
		dst[start + i] = src[i];
	return (0);
}