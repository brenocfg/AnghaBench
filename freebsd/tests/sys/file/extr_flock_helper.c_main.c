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
struct statfs {int /*<<< orphan*/  f_fstypename; } ;
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct TYPE_3__ {int num; int /*<<< orphan*/  (* testfn ) (int,int,char const**) ;scalar_t__ intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fstatfs (int,struct statfs*) ; 
 int /*<<< orphan*/  ignore_alarm ; 
 int make_file (char const*,int) ; 
 unsigned int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int,char const**) ; 
 TYPE_1__* tests ; 

int
main(int argc, const char *argv[])
{
	int testnum;
	int fd;
	int nointr;
	unsigned i;
	struct sigaction sa;
	int test_argc;
	const char **test_argv;

	if (argc < 2) {
		errx(1, "usage: flock <directory> [test number] ...");
	}

	fd = make_file(argv[1], 1024);
	if (argc >= 3) {
		testnum = strtol(argv[2], NULL, 0);
		test_argc = argc - 2;
		test_argv = argv + 2;
	} else {
		testnum = 0;
		test_argc = 0;
		test_argv = NULL;
	}

	sa.sa_handler = ignore_alarm;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGALRM, &sa, 0);

	nointr = 0;
#if defined(__FreeBSD__) && __FreeBSD_version < 800040
	{
		/*
		 * FreeBSD with userland NLM can't interrupt a blocked
		 * lock request on an NFS mounted filesystem.
		 */
		struct statfs st;
		fstatfs(fd, &st);
		nointr = !strcmp(st.f_fstypename, "nfs");
	}
#endif

	for (i = 0; i < nitems(tests); i++) {
		if (tests[i].intr && nointr)
			continue;
		if (!testnum || tests[i].num == testnum)
			tests[i].testfn(fd, test_argc, test_argv);
	}

	return 0;
}