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
typedef  int /*<<< orphan*/  uargs ;
struct ufs_args {int /*<<< orphan*/  fspec; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSTEST_MNTNAME ; 
 int /*<<< orphan*/  MNT_LOG ; 
 int /*<<< orphan*/  MOUNT_FFS ; 
 int /*<<< orphan*/  RUMP_DAEMONIZE_SUCCESS ; 
 int /*<<< orphan*/  RUMP_ETFS_BLK ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  __UNCONST (char*) ; 
 int background ; 
 int /*<<< orphan*/  die (char*,int) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int rump_daemonize_begin () ; 
 int /*<<< orphan*/  rump_daemonize_done (int /*<<< orphan*/ ) ; 
 int rump_init () ; 
 int rump_init_server (char const*) ; 
 int /*<<< orphan*/  rump_pub_etfs_register (char*,char const*,int /*<<< orphan*/ ) ; 
 int rump_sys_mkdir (int /*<<< orphan*/ ,int) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ufs_args*,int) ; 
 int /*<<< orphan*/  rump_sys_reboot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigreboot ; 
 int /*<<< orphan*/  sigsem ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  usage () ; 

int 
main(int argc, char **argv)
{
	int error;
	struct ufs_args uargs;
	const char *filename;
	const char *serverurl;
	int log = 0;
	int ch;

	while ((ch = getopt(argc, argv, "bl")) != -1) {
		switch(ch) {
		case 'b':
			background = 1;
			break;
		case 'l':
			log = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	filename = argv[0];
	serverurl = argv[1];

	if (background) {
		error = rump_daemonize_begin();
		if (error)
			errx(1, "rump daemonize: %s", strerror(error));
	}

	error = rump_init();
	if (error)
		die("rump init failed", error);

	if (rump_sys_mkdir(FSTEST_MNTNAME, 0777) == -1)
		die("mount point create", errno);
	rump_pub_etfs_register("/diskdev", filename, RUMP_ETFS_BLK);
	uargs.fspec = __UNCONST("/diskdev");
	if (rump_sys_mount(MOUNT_FFS, FSTEST_MNTNAME, (log) ? MNT_LOG : 0,
	    &uargs, sizeof(uargs)) == -1)
		die("mount ffs", errno);

	error = rump_init_server(serverurl);
	if (error)
		die("rump server init failed", error);
	if (background)
		rump_daemonize_done(RUMP_DAEMONIZE_SUCCESS);

	sem_init(&sigsem, 0, 0);
	signal(SIGTERM, sigreboot);
	signal(SIGINT, sigreboot);
	sem_wait(&sigsem);

	rump_sys_reboot(0, NULL);
	/*NOTREACHED*/
	return 0;
}