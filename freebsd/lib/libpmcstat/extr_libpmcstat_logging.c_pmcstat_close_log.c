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
struct pmcstat_args {int pa_logfd; int pa_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int FLAG_HAS_PIPE ; 
 int PMCSTAT_EXITING ; 
 int PMCSTAT_FINISHED ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pmc_close_logfile () ; 

int
pmcstat_close_log(struct pmcstat_args *args)
{
	/* If a local logfile is configured ask the kernel to stop
	 * and flush data. Kernel will close the file when data is flushed
	 * so keep the status to EXITING.
	 */
	if (args->pa_logfd != -1) {
		if (pmc_close_logfile() < 0)
			err(EX_OSERR, "ERROR: logging failed");
	}

	return (args->pa_flags & FLAG_HAS_PIPE ? PMCSTAT_EXITING :
	    PMCSTAT_FINISHED);
}