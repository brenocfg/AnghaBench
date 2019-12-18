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
 int /*<<< orphan*/  SLAVE_CLEAR ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  uv_nmi_cpus_in_nmi ; 
 int /*<<< orphan*/  uv_nmi_slave_continue ; 

__attribute__((used)) static void uv_nmi_sync_exit(int master)
{
	atomic_dec(&uv_nmi_cpus_in_nmi);
	if (master) {
		while (atomic_read(&uv_nmi_cpus_in_nmi) > 0)
			cpu_relax();
		atomic_set(&uv_nmi_slave_continue, SLAVE_CLEAR);
	} else {
		while (atomic_read(&uv_nmi_slave_continue))
			cpu_relax();
	}
}