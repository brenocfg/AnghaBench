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
struct pmc_op_getdriverstats {int /*<<< orphan*/  pm_log_sweeps; int /*<<< orphan*/  pm_buffer_requests_failed; int /*<<< orphan*/  pm_buffer_requests; int /*<<< orphan*/  pm_syscall_errors; int /*<<< orphan*/  pm_syscalls; int /*<<< orphan*/  pm_intr_bufferfull; int /*<<< orphan*/  pm_intr_processed; int /*<<< orphan*/  pm_intr_ignored; } ;
struct pmc_driverstats {int /*<<< orphan*/  pm_log_sweeps; int /*<<< orphan*/  pm_buffer_requests_failed; int /*<<< orphan*/  pm_buffer_requests; int /*<<< orphan*/  pm_syscall_errors; int /*<<< orphan*/  pm_syscalls; int /*<<< orphan*/  pm_intr_bufferfull; int /*<<< orphan*/  pm_intr_processed; int /*<<< orphan*/  pm_intr_ignored; } ;

/* Variables and functions */
 int /*<<< orphan*/  GETDRIVERSTATS ; 
 scalar_t__ PMC_CALL (int /*<<< orphan*/ ,struct pmc_op_getdriverstats*) ; 

int
pmc_get_driver_stats(struct pmc_driverstats *ds)
{
	struct pmc_op_getdriverstats gms;

	if (PMC_CALL(GETDRIVERSTATS, &gms) < 0)
		return (-1);

	/* copy out fields in the current userland<->library interface */
	ds->pm_intr_ignored    = gms.pm_intr_ignored;
	ds->pm_intr_processed  = gms.pm_intr_processed;
	ds->pm_intr_bufferfull = gms.pm_intr_bufferfull;
	ds->pm_syscalls        = gms.pm_syscalls;
	ds->pm_syscall_errors  = gms.pm_syscall_errors;
	ds->pm_buffer_requests = gms.pm_buffer_requests;
	ds->pm_buffer_requests_failed = gms.pm_buffer_requests_failed;
	ds->pm_log_sweeps      = gms.pm_log_sweeps;
	return (0);
}