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
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  plugins ; 
 int /*<<< orphan*/  pmcstat_initialize_logging (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcstat_kernproc ; 
 int /*<<< orphan*/  pmcstat_mergepmc ; 
 int /*<<< orphan*/  pmcstat_npmcs ; 

void
pmcstat_log_initialize_logging(void)
{

	pmcstat_initialize_logging(&pmcstat_kernproc,
	    &args, plugins, &pmcstat_npmcs, &pmcstat_mergepmc);
}