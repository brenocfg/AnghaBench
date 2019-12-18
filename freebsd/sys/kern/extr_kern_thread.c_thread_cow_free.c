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
struct thread {int /*<<< orphan*/ * td_limit; int /*<<< orphan*/ * td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lim_free (int /*<<< orphan*/ *) ; 

void
thread_cow_free(struct thread *td)
{

	if (td->td_ucred != NULL)
		crfree(td->td_ucred);
	if (td->td_limit != NULL)
		lim_free(td->td_limit);
}