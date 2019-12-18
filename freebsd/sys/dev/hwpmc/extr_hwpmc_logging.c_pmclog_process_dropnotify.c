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
struct pmclog_dropnotify {int dummy; } ;
struct pmc_owner {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROPNOTIFY ; 
 int /*<<< orphan*/  PMCLOG_DESPATCH (struct pmc_owner*) ; 
 int /*<<< orphan*/  PMCLOG_RESERVE (struct pmc_owner*,int /*<<< orphan*/ ,int) ; 

void
pmclog_process_dropnotify(struct pmc_owner *po)
{
	PMCLOG_RESERVE(po,DROPNOTIFY,sizeof(struct pmclog_dropnotify));
	PMCLOG_DESPATCH(po);
}