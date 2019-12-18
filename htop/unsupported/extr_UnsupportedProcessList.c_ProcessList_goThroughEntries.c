#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pid; int ppid; char* comm; int updated; char state; int show; double percent_cpu; double percent_mem; char* user; int nlwp; int starttime_ctime; int m_size; int m_resident; int minflt; int majflt; int /*<<< orphan*/  starttime_show; scalar_t__ nice; scalar_t__ priority; scalar_t__ processor; scalar_t__ flags; scalar_t__ st_uid; scalar_t__ tpgid; scalar_t__ tty_nr; scalar_t__ session; scalar_t__ pgrp; scalar_t__ basenameOffset; scalar_t__ tgid; scalar_t__ time; } ;
typedef  int /*<<< orphan*/  ProcessList ;
typedef  TYPE_1__ Process ;

/* Variables and functions */
 TYPE_1__* ProcessList_getProcess (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnsupportedProcess_new ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

void ProcessList_goThroughEntries(ProcessList* super) {
	bool preExisting = true;
    Process *proc;

    proc = ProcessList_getProcess(super, 1, &preExisting, UnsupportedProcess_new);

    /* Empty values */
    proc->time = proc->time + 10;
    proc->pid  = 1;
    proc->ppid = 1;
    proc->tgid = 0;
    proc->comm = "<unsupported architecture>";
    proc->basenameOffset = 0;
    proc->updated = true;

    proc->state = 'R';
    proc->show = true; /* Reflected in proc->settings-> "hideXXX" really */
    proc->pgrp = 0;
    proc->session = 0;
    proc->tty_nr = 0;
    proc->tpgid = 0;
    proc->st_uid = 0;
    proc->flags = 0;
    proc->processor = 0;

    proc->percent_cpu = 2.5;
    proc->percent_mem = 2.5;
    proc->user = "nobody";

    proc->priority = 0;
    proc->nice = 0;
    proc->nlwp = 1;
    strncpy(proc->starttime_show, "Jun 01 ", sizeof(proc->starttime_show));
    proc->starttime_ctime = 1433116800; // Jun 01, 2015

    proc->m_size = 100;
    proc->m_resident = 100;

    proc->minflt = 20;
    proc->majflt = 20;
}