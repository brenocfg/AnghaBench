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
struct process {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/ * STRjobcmd ; 
 int /*<<< orphan*/ * STRunalias ; 
 scalar_t__ adrof1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aliases ; 
 int /*<<< orphan*/  aliasrun (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disabled_cleanup ; 
 int jobcmd_active ; 
 struct process* pcurrjob ; 
 int /*<<< orphan*/  pintr_disabled ; 
 scalar_t__ whyles ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

void
job_cmd(Char *args)
{
    if (whyles)
	return;
    pintr_disabled++;
    cleanup_push(&pintr_disabled, disabled_cleanup);
    if (jobcmd_active) {	/* an error must have been caught */
	aliasrun(2, STRunalias, STRjobcmd);
	xprintf("%s", CGETS(22, 14, "Faulty alias 'jobcmd' removed.\n"));
	goto leave;
    }
    jobcmd_active = 1;
    if (!whyles && adrof1(STRjobcmd, &aliases)) {
	struct process *pp = pcurrjob; /* put things back after the hook */
	aliasrun(2, STRjobcmd, args);
	pcurrjob = pp;
    }
leave:
    jobcmd_active = 0;
    cleanup_until(&pintr_disabled);
}