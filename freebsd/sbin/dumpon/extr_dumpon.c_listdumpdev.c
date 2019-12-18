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
struct diocskerneldump_arg {int /*<<< orphan*/  kda_gateway; int /*<<< orphan*/  kda_af; int /*<<< orphan*/  kda_client; int /*<<< orphan*/  kda_server; } ;
typedef  int /*<<< orphan*/  ip ;
typedef  int /*<<< orphan*/  dumpdev ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGKERNELDUMP ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  _PATH_NETDUMP ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errno ; 
 char* inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct diocskerneldump_arg*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ sysctlbyname (char const*,char**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
listdumpdev(void)
{
	static char ip[200];

	char dumpdev[PATH_MAX];
	struct diocskerneldump_arg ndconf;
	size_t len;
	const char *sysctlname = "kern.shutdown.dumpdevname";
	int fd;

	len = sizeof(dumpdev);
	if (sysctlbyname(sysctlname, &dumpdev, &len, NULL, 0) != 0) {
		if (errno == ENOMEM) {
			err(EX_OSERR, "Kernel returned too large of a buffer for '%s'\n",
				sysctlname);
		} else {
			err(EX_OSERR, "Sysctl get '%s'\n", sysctlname);
		}
	}
	if (strlen(dumpdev) == 0)
		(void)strlcpy(dumpdev, _PATH_DEVNULL, sizeof(dumpdev));

	if (verbose) {
		char *ctx, *dd;
		unsigned idx;

		printf("kernel dumps on priority: device\n");
		idx = 0;
		ctx = dumpdev;
		while ((dd = strsep(&ctx, ",")) != NULL)
			printf("%u: %s\n", idx++, dd);
	} else
		printf("%s\n", dumpdev);

	/* If netdump is enabled, print the configuration parameters. */
	if (verbose) {
		fd = open(_PATH_NETDUMP, O_RDONLY);
		if (fd < 0) {
			if (errno != ENOENT)
				err(EX_OSERR, "opening %s", _PATH_NETDUMP);
			return;
		}
		if (ioctl(fd, DIOCGKERNELDUMP, &ndconf) != 0) {
			if (errno != ENXIO)
				err(EX_OSERR, "ioctl(DIOCGKERNELDUMP)");
			(void)close(fd);
			return;
		}

		printf("server address: %s\n",
		    inet_ntop(ndconf.kda_af, &ndconf.kda_server, ip,
			sizeof(ip)));
		printf("client address: %s\n",
		    inet_ntop(ndconf.kda_af, &ndconf.kda_client, ip,
			sizeof(ip)));
		printf("gateway address: %s\n",
		    inet_ntop(ndconf.kda_af, &ndconf.kda_gateway, ip,
			sizeof(ip)));
		(void)close(fd);
	}
}