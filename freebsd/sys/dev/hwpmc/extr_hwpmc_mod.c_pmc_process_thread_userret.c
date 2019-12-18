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
struct thread {int /*<<< orphan*/  td_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_UR ; 
 int /*<<< orphan*/  curcpu ; 
 int /*<<< orphan*/  pmc_capture_user_callchain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 

__attribute__((used)) static void
pmc_process_thread_userret(struct thread *td)
{
	sched_pin();
	pmc_capture_user_callchain(curcpu, PMC_UR, td->td_frame);
	sched_unpin();
}