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
struct thread {scalar_t__ td_tid; } ;
typedef  scalar_t__ lwpid_t ;

/* Variables and functions */
 struct thread* kdb_thr_first () ; 
 struct thread* kdb_thr_next (struct thread*) ; 

struct thread *
kdb_thr_lookup(lwpid_t tid)
{
	struct thread *thr;

	thr = kdb_thr_first();
	while (thr != NULL && thr->td_tid != tid)
		thr = kdb_thr_next(thr);
	return (thr);
}