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
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pf_dev ; 
 int /*<<< orphan*/  pf_end_lock ; 
 int pf_end_threads ; 
 int /*<<< orphan*/  pf_ioctl_lock ; 
 int /*<<< orphan*/  pf_purge_proc ; 
 int /*<<< orphan*/  pf_purge_thread ; 
 int /*<<< orphan*/  pf_rules_lock ; 
 int /*<<< orphan*/  pfi_cleanup () ; 
 int /*<<< orphan*/  rm_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pf_unload(void)
{

	sx_xlock(&pf_end_lock);
	pf_end_threads = 1;
	while (pf_end_threads < 2) {
		wakeup_one(pf_purge_thread);
		sx_sleep(pf_purge_proc, &pf_end_lock, 0, "pftmo", 0);
	}
	sx_xunlock(&pf_end_lock);

	if (pf_dev != NULL)
		destroy_dev(pf_dev);

	pfi_cleanup();

	rm_destroy(&pf_rules_lock);
	sx_destroy(&pf_ioctl_lock);
	sx_destroy(&pf_end_lock);
}