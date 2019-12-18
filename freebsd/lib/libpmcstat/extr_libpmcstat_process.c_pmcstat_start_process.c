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
 int /*<<< orphan*/  EX_OSERR ; 
 size_t PARENTSOCKET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int write (int,char*,int) ; 

void
pmcstat_start_process(int *pmcstat_sockpair)
{
	/* Signal the child to proceed. */
	if (write(pmcstat_sockpair[PARENTSOCKET], "!", 1) != 1)
		err(EX_OSERR, "ERROR (parent): write of token failed");

	(void) close(pmcstat_sockpair[PARENTSOCKET]);
}