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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 long long SPINUNIT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndelay (long long) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  touch_nmi_watchdog () ; 

__attribute__((used)) static int __wait_for_cpus(atomic_t *t, long long timeout)
{
	int all_cpus = num_online_cpus();

	atomic_inc(t);

	while (atomic_read(t) < all_cpus) {
		if (timeout < SPINUNIT) {
			pr_err("Timeout while waiting for CPUs rendezvous, remaining: %d\n",
				all_cpus - atomic_read(t));
			return 1;
		}

		ndelay(SPINUNIT);
		timeout -= SPINUNIT;

		touch_nmi_watchdog();
	}
	return 0;
}