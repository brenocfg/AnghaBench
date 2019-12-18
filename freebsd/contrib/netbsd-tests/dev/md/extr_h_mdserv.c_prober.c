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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int EPIPE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  REQUIRE (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int rump_daemonize_done (int) ; 
 int rump_sys_open (void*,int /*<<< orphan*/ ) ; 
 int rump_sys_read (int,char*,int) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void *
prober(void *arg)
{
	int fd, error;
	char buf[4];
	ssize_t n;

	fd = rump_sys_open(arg, O_RDONLY);
	for (;;) {
		n = rump_sys_read(fd, buf, sizeof(buf));

		switch (n) {
		case 4:
			error = 0;
			goto out;

		case -1:
			if (errno == ENXIO) {
				usleep(1000);
				continue;
			}

			/* FALLTHROUGH */
		default:
			error = EPIPE;
			goto out;
		}
	}
 out:

	error = rump_daemonize_done(error);
	REQUIRE(error, "rump_daemonize_done");

	if (error)
		exit(1);

	return NULL;
}