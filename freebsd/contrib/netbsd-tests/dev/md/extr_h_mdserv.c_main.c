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
struct md_conf {int /*<<< orphan*/  md_type; int /*<<< orphan*/  md_size; int /*<<< orphan*/  md_addr; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  MDSIZE ; 
 int /*<<< orphan*/  MD_SETCONF ; 
 int /*<<< orphan*/  MD_UMEM_SERVER ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  REQUIRE (int,char*) ; 
 int /*<<< orphan*/  calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  prober ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 
 int rump_daemonize_begin () ; 
 int /*<<< orphan*/  rump_daemonize_done (int /*<<< orphan*/ ) ; 
 int rump_init () ; 
 int rump_init_server (char*) ; 
 int rump_sys_ioctl (int,int /*<<< orphan*/ ,struct md_conf*) ; 
 int rump_sys_open (char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	pthread_t pt;
	struct md_conf md;
	int fd, error;

	if (argc != 2)
		exit(1);

	md.md_addr = calloc(1, MDSIZE);
	md.md_size = MDSIZE;
	md.md_type = MD_UMEM_SERVER;

	error = rump_daemonize_begin();
	REQUIRE(error, "rump_daemonize_begin");

	error = rump_init();
	REQUIRE(error, "rump_init");

	error = rump_init_server("unix://commsock");
	REQUIRE(error, "init server");

	if ((fd = rump_sys_open(argv[1], O_RDWR)) == -1)
		err(1, "open");

	/*
	 * Now, configuring the md driver also causes our process
	 * to start acting as the worker for the md.  Splitting it
	 * into two steps in the driver is not easy, since md is
	 * supposed to be unconfigured when the process dies
	 * (process may exit between calling ioctl1 and ioctl2).
	 * So, start a probe thread which attempts to read the md
	 * and declares the md as configured when the read is
	 * succesful.
	 */
	error = pthread_create(&pt, NULL, prober, argv[1]);
	REQUIRE(error, "pthread_create");
	pthread_detach(pt);

	if (rump_sys_ioctl(fd, MD_SETCONF, &md) == -1) {
		rump_daemonize_done(errno);
		exit(1);
	}

	return 0;
}