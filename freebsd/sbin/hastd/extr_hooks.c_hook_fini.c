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
struct hookproc {scalar_t__ hp_magic; scalar_t__ hp_pid; } ;

/* Variables and functions */
 scalar_t__ HOOKPROC_MAGIC_ONLIST ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 struct hookproc* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hook_free (struct hookproc*) ; 
 int /*<<< orphan*/  hook_remove (struct hookproc*) ; 
 int /*<<< orphan*/  hookprocs ; 
 int /*<<< orphan*/  hookprocs_lock ; 
 int hooks_initialized ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
hook_fini(void)
{
	struct hookproc *hp;

	PJDLOG_ASSERT(hooks_initialized);

	mtx_lock(&hookprocs_lock);
	while ((hp = TAILQ_FIRST(&hookprocs)) != NULL) {
		PJDLOG_ASSERT(hp->hp_magic == HOOKPROC_MAGIC_ONLIST);
		PJDLOG_ASSERT(hp->hp_pid > 0);

		hook_remove(hp);
		hook_free(hp);
	}
	mtx_unlock(&hookprocs_lock);

	mtx_destroy(&hookprocs_lock);
	TAILQ_INIT(&hookprocs);
	hooks_initialized = false;
}