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
struct wdog_mode {int wc_count; char* wc_names; int wm_period; int /*<<< orphan*/  wm_mode; int /*<<< orphan*/  wm_name; } ;
struct wdog_conf {int wc_count; char* wc_names; int wm_period; int /*<<< orphan*/  wm_mode; int /*<<< orphan*/  wm_name; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int,int) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  WDOGIOC_GWDOGS ; 
 int /*<<< orphan*/  WDOGIOC_SMODE ; 
 int /*<<< orphan*/  WDOGIOC_TICKLE ; 
 int /*<<< orphan*/  WDOG_MODE_DISARMED ; 
 int /*<<< orphan*/  WDOG_MODE_ETICKLE ; 
 int WDOG_NAMESIZE ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  getppid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rump_init () ; 
 int rump_sys_ioctl (int,int /*<<< orphan*/ ,...) ; 
 int rump_sys_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigcount ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int tcount ; 
 int /*<<< orphan*/  usleep (int) ; 
 int wait (int*) ; 

__attribute__((used)) static int
testbody(int max)
{
	char wname[WDOG_NAMESIZE];
	struct wdog_conf wc;
	struct wdog_mode wm;
	pid_t p1, p2;
	int status;
	int fd;

	signal(SIGUSR1, sigcount);

	switch ((p1 = fork())) {
	case 0:
		break;
	case -1:
		atf_tc_fail_errno("fork");
		break;
	default:
		p2 = wait(&status);
		ATF_REQUIRE_EQ(p1, p2);
		ATF_REQUIRE_EQ(tcount, max);
		return status;
	}

	rump_init();

	fd = rump_sys_open("/dev/watchdog", O_RDWR);
	if (fd == -1)
		err(1, "open watchdog");

	wc.wc_count = 1;
	wc.wc_names = wname;

	if (rump_sys_ioctl(fd, WDOGIOC_GWDOGS, &wc) == -1)
		err(1, "can't fetch watchdog names");

	if (wc.wc_count) {
		assert(wc.wc_count == 1);

		strlcpy(wm.wm_name, wc.wc_names, sizeof(wm.wm_name));
		wm.wm_mode = WDOG_MODE_ETICKLE;
		wm.wm_period = 1;
		if (rump_sys_ioctl(fd, WDOGIOC_SMODE, &wm) == -1)
			atf_tc_fail_errno("failed to set tickle");

		usleep(400000);
		if (max == 1)
			rump_sys_ioctl(fd, WDOGIOC_TICKLE);
		else {
			wm.wm_mode = WDOG_MODE_DISARMED;
			rump_sys_ioctl(fd, WDOGIOC_SMODE, &wm);
		}
		kill(getppid(), SIGUSR1);

		sleep(2);
		printf("staying alive\n");
		kill(getppid(), SIGUSR1);
		_exit(2);
	}
	/* fail */
	printf("no watchdog registered!\n");
	_exit(1);
}