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
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TSUNWAIT (char*) ; 
 int /*<<< orphan*/  TSWAIT (char*) ; 
 int WARNING_INTERVAL_SECS ; 
 int hz ; 
 int /*<<< orphan*/  intr_config_hook_list ; 
 int /*<<< orphan*/  intr_config_hook_lock ; 
 scalar_t__ msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_interrupt_driven_config_hooks () ; 
 int /*<<< orphan*/  run_interrupt_driven_config_hooks_warning (int) ; 

__attribute__((used)) static void
boot_run_interrupt_driven_config_hooks(void *dummy)
{
	int warned;

	run_interrupt_driven_config_hooks();

	/* Block boot processing until all hooks are disestablished. */
	TSWAIT("config hooks");
	mtx_lock(&intr_config_hook_lock);
	warned = 0;
	while (!TAILQ_EMPTY(&intr_config_hook_list)) {
		if (msleep(&intr_config_hook_list, &intr_config_hook_lock,
		    0, "conifhk", WARNING_INTERVAL_SECS * hz) ==
		    EWOULDBLOCK) {
			mtx_unlock(&intr_config_hook_lock);
			warned++;
			run_interrupt_driven_config_hooks_warning(warned);
			mtx_lock(&intr_config_hook_lock);
		}
	}
	mtx_unlock(&intr_config_hook_lock);
	TSUNWAIT("config hooks");
}