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
struct thread {int /*<<< orphan*/  td_cowgen; int /*<<< orphan*/  td_limit; int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lim_hold (int /*<<< orphan*/ ) ; 

void
thread_cow_get(struct thread *newtd, struct thread *td)
{

	newtd->td_ucred = crhold(td->td_ucred);
	newtd->td_limit = lim_hold(td->td_limit);
	newtd->td_cowgen = td->td_cowgen;
}