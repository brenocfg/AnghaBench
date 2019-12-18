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
struct procstat_cmd {int /*<<< orphan*/  (* cmd ) (struct procstat*,struct kinfo_proc*) ;} ;
struct procstat {int dummy; } ;
struct kinfo_proc {int /*<<< orphan*/  ki_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stub1 (struct procstat*,struct kinfo_proc*) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_errc (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 

__attribute__((used)) static void
procstat(const struct procstat_cmd *cmd, struct procstat *prstat,
    struct kinfo_proc *kipp)
{
	char *pidstr = NULL;

	asprintf(&pidstr, "%d", kipp->ki_pid);
	if (pidstr == NULL)
		xo_errc(1, ENOMEM, "Failed to allocate memory in procstat()");
	xo_open_container(pidstr);
	cmd->cmd(prstat, kipp);
	xo_close_container(pidstr);
	free(pidstr);
}