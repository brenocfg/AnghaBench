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

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PI_SWI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWI_TQ ; 
 scalar_t__ mca_banks ; 
 int /*<<< orphan*/  mca_resize_freelist () ; 
 int /*<<< orphan*/  mca_tq ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static void
mca_createtq(void *dummy)
{
	if (mca_banks <= 0)
		return;

	mca_tq = taskqueue_create_fast("mca", M_WAITOK,
	    taskqueue_thread_enqueue, &mca_tq);
	taskqueue_start_threads(&mca_tq, 1, PI_SWI(SWI_TQ), "mca taskq");

	/* CMCIs during boot may have claimed items from the freelist. */
	mca_resize_freelist();
}