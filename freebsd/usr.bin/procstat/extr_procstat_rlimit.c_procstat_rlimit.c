#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rlimit {int /*<<< orphan*/  rlim_max; int /*<<< orphan*/  rlim_cur; } ;
struct procstat {int dummy; } ;
struct kinfo_proc {int /*<<< orphan*/  ki_comm; int /*<<< orphan*/  ki_pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int PS_OPT_NOHEADER ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int RLIM_NLIMITS ; 
 int /*<<< orphan*/  humanize_rlimit (int,int /*<<< orphan*/ ) ; 
 int procstat_getrlimit (struct procstat*,struct kinfo_proc*,int,struct rlimit*) ; 
 int procstat_opts ; 
 TYPE_1__* rlimit_param ; 
 int /*<<< orphan*/  xo_close_container (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_container (int /*<<< orphan*/ ) ; 

void
procstat_rlimit(struct procstat *prstat, struct kinfo_proc *kipp)
{
	struct rlimit rlimit;
	int i;

	if ((procstat_opts & PS_OPT_NOHEADER) == 0) {
		xo_emit("{T:/%5s %-16s %-16s %16s %16s}\n",
		    "PID", "COMM", "RLIMIT", "SOFT     ", "HARD     ");
	}
	xo_emit("{ek:process_id/%5d}{e:command/%-16s/%s}", kipp->ki_pid,
	    kipp->ki_comm);
	for (i = 0; i < RLIM_NLIMITS; i++) {
		if (procstat_getrlimit(prstat, kipp, i, &rlimit) == -1)
			return;
		xo_emit("{dk:process_id/%5d} {d:command/%-16s} "
		    "{d:rlimit_param/%-16s} ", kipp->ki_pid, kipp->ki_comm,
		    rlimit_param[i].name);

		xo_open_container(rlimit_param[i].name);
		if (rlimit.rlim_cur == RLIM_INFINITY)
			xo_emit("{e:soft_limit/infinity}");
		else
			xo_emit("{e:soft_limit/%U}", rlimit.rlim_cur);

		if (rlimit.rlim_max == RLIM_INFINITY)
			xo_emit("{e:hard_limit/infinity}");
		else
			xo_emit("{e:hard_limit/%U}", rlimit.rlim_max);
		xo_close_container(rlimit_param[i].name);

		xo_emit("{d:rlim_cur/%16s} ",
		    humanize_rlimit(i, rlimit.rlim_cur));
		xo_emit("{d:rlim_max/%16s}\n",
		    humanize_rlimit(i, rlimit.rlim_max));
	}
}