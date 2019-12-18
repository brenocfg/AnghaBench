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
struct thread {int dummy; } ;
struct proc {scalar_t__ p_numthreads; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROCLIM ; 
 int /*<<< orphan*/  max_threads_hits ; 
 scalar_t__ max_threads_per_proc ; 
 struct thread* thread_alloc (int) ; 

int
kern_thr_alloc(struct proc *p, int pages, struct thread **ntd)
{

	/* Have race condition but it is cheap. */
	if (p->p_numthreads >= max_threads_per_proc) {
		++max_threads_hits;
		return (EPROCLIM);
	}

	*ntd = thread_alloc(pages);
	if (*ntd == NULL)
		return (ENOMEM);

	return (0);
}