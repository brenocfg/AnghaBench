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
struct thread {scalar_t__ td_vp_reserv; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_subtract_long (int /*<<< orphan*/ *,scalar_t__) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  numvnodes ; 

void
getnewvnode_drop_reserve(void)
{
	struct thread *td;

	td = curthread;
	atomic_subtract_long(&numvnodes, td->td_vp_reserv);
	td->td_vp_reserv = 0;
}