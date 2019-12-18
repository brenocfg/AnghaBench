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
struct intr_config_hook {int /*<<< orphan*/  ich_arg; int /*<<< orphan*/  (* ich_func ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct intr_config_hook* TAILQ_NEXT (struct intr_config_hook*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ich_links ; 
 int /*<<< orphan*/  intr_config_hook_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct intr_config_hook* next_to_notify ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_interrupt_driven_config_hooks()
{
	static int running;
	struct intr_config_hook *hook_entry;

	mtx_lock(&intr_config_hook_lock);

	/*
	 * If hook processing is already active, any newly
	 * registered hooks will eventually be notified.
	 * Let the currently running session issue these
	 * notifications.
	 */
	if (running != 0) {
		mtx_unlock(&intr_config_hook_lock);
		return;
	}
	running = 1;

	while (next_to_notify != NULL) {
		hook_entry = next_to_notify;
		next_to_notify = TAILQ_NEXT(hook_entry, ich_links);
		mtx_unlock(&intr_config_hook_lock);
		(*hook_entry->ich_func)(hook_entry->ich_arg);
		mtx_lock(&intr_config_hook_lock);
	}

	running = 0;
	mtx_unlock(&intr_config_hook_lock);
}