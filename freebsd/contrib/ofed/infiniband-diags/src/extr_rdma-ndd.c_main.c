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
struct ibdiag_opt {char* member_0; char member_1; int member_2; char* member_3; char* member_4; } ;
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 scalar_t__ DEFAULT_ND_FORMAT ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int LOG_PERROR ; 
 int LOG_PID ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SYS_HOSTNAME ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closelog () ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreground ; 
 scalar_t__ ibd_nd_format ; 
 int /*<<< orphan*/  ibdiag_process_opts (int,char**,int /*<<< orphan*/ *,char*,struct ibdiag_opt const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  monitor () ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_opts ; 
 scalar_t__ read_hostname (int,char*,int) ; 
 int /*<<< orphan*/  remove_pidfile () ; 
 int /*<<< orphan*/  set_rdma_node_desc (char const*,int) ; 
 int /*<<< orphan*/  setup_udev () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  write_pidfile () ; 

int main(int argc, char *argv[])
{
	int fd;
	char hostname[128];

	openlog("rdma-ndd", LOG_PID | LOG_PERROR, LOG_DAEMON);

	const struct ibdiag_opt opts[] = {
		{"retry_timer", 't', 1, "<retry_timer>",
			"Length of time to sleep when system errors occur "
			"when attempting to poll and or read the hostname "
			"from the system.\n"},
		{"retry_count", 'r', 1, "<retry_count>",
			"Number of times to attempt to retry setting "
			"of the node description on failure\n"},
		{"foreground", 'f', 0, NULL, "run in the foreground instead of as a daemon\n"},
		{"pidfile", 0, 1, "<pidfile>", "specify a pid file (daemon mode only)\n"},
		{0}
	};

	ibdiag_process_opts(argc, argv, NULL, "CPDLGtsKyevd", opts,
			    process_opts, "", NULL);

	if (!ibd_nd_format)
		ibd_nd_format = DEFAULT_ND_FORMAT;

	if (!foreground) {
		closelog();
		openlog("rdma-ndd", LOG_PID, LOG_DAEMON);
		if (daemon(0, 0) != 0) {
			syslog(LOG_ERR, "Failed to daemonize\n");
			exit(errno);
		}
		write_pidfile();
	}

	setup_udev();

	syslog(LOG_INFO, "Node Descriptor format (%s)\n", ibd_nd_format);

	fd = open(SYS_HOSTNAME, O_RDONLY);
	if (read_hostname(fd, hostname, sizeof(hostname)) != 0)
		hostname[0] = '\0';
	set_rdma_node_desc((const char *)hostname, 1);
	close(fd);

	monitor();

	remove_pidfile();

	return 0;
}