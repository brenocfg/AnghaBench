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
 int ERROR_EXIT ; 
 int /*<<< orphan*/  LC_ALL ; 
 int OK_EXIT ; 
 int Option ; 
 int /*<<< orphan*/  Pid ; 
 char* ProgramName ; 
 int /*<<< orphan*/  RealUser ; 
 int /*<<< orphan*/  User ; 
 int /*<<< orphan*/  allowed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_cmd () ; 
 int /*<<< orphan*/  edit_cmd () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  list_cmd () ; 
 int /*<<< orphan*/  log_it (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
#define  opt_delete 132 
#define  opt_edit 131 
#define  opt_list 130 
#define  opt_replace 129 
#define  opt_unknown 128 
 int /*<<< orphan*/  parse_args (int,char**) ; 
 int /*<<< orphan*/  replace_cmd () ; 
 int /*<<< orphan*/  set_cron_cwd () ; 
 int /*<<< orphan*/  set_cron_uid () ; 
 int /*<<< orphan*/  setlinebuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	int	exitstatus;

	Pid = getpid();
	ProgramName = argv[0];

#if defined(POSIX)
	setlocale(LC_ALL, "");
#endif

#if defined(BSD)
	setlinebuf(stderr);
#endif
	parse_args(argc, argv);		/* sets many globals, opens a file */
	set_cron_uid();
	set_cron_cwd();
	if (!allowed(User)) {
		warnx("you (%s) are not allowed to use this program", User);
		log_it(RealUser, Pid, "AUTH", "crontab command not allowed");
		exit(ERROR_EXIT);
	}
	exitstatus = OK_EXIT;
	switch (Option) {
	case opt_list:		list_cmd();
				break;
	case opt_delete:	delete_cmd();
				break;
	case opt_edit:		edit_cmd();
				break;
	case opt_replace:	if (replace_cmd() < 0)
					exitstatus = ERROR_EXIT;
				break;
	case opt_unknown:
				break;
	}
	exit(exitstatus);
	/*NOTREACHED*/
}