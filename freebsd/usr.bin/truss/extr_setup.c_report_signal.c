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
struct trussinfo {int /*<<< orphan*/  outfile; struct threadinfo* curthread; } ;
struct threadinfo {int /*<<< orphan*/  after; } ;
struct ptrace_lwpinfo {scalar_t__ pl_event; int pl_flags; int /*<<< orphan*/  pl_siginfo; } ;
struct TYPE_3__ {int si_status; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ PL_EVENT_SIGNAL ; 
 int PL_FLAG_SI ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_siginfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_line_prefix (struct trussinfo*) ; 
 char* sysdecode_signal (int) ; 

__attribute__((used)) static void
report_signal(struct trussinfo *info, siginfo_t *si, struct ptrace_lwpinfo *pl)
{
	struct threadinfo *t;
	const char *signame;

	t = info->curthread;
	clock_gettime(CLOCK_REALTIME, &t->after);
	print_line_prefix(info);
	signame = sysdecode_signal(si->si_status);
	if (signame == NULL)
		signame = "?";
	fprintf(info->outfile, "SIGNAL %u (%s)", si->si_status, signame);
	if (pl->pl_event == PL_EVENT_SIGNAL && pl->pl_flags & PL_FLAG_SI)
		decode_siginfo(info->outfile, &pl->pl_siginfo);
	fprintf(info->outfile, "\n");
	
}