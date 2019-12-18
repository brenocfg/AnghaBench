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
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hookprocs ; 
 int /*<<< orphan*/  hookprocs_lock ; 
 int hooks_initialized ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *) ; 

void
hook_init(void)
{

	PJDLOG_ASSERT(!hooks_initialized);

	mtx_init(&hookprocs_lock);
	TAILQ_INIT(&hookprocs);
	hooks_initialized = true;
}