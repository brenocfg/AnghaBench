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
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  IOCTL 129 
 int /*<<< orphan*/  SIOCSIFMTU ; 
#define  SOCKET 128 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ifconfig_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifconfig_err_errno (int /*<<< orphan*/ *) ; 
 int ifconfig_err_errtype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifconfig_err_ioctlreq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ifconfig_open () ; 
 scalar_t__ ifconfig_set_mtu (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strdup (char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char *argv[])
{
	char *ifname, *ptr;
	int mtu;
	ifconfig_handle_t *lifh;

	if (argc != 3) {
		errx(EINVAL, "Invalid number of arguments."
		    " First argument should be interface name, second argument"
		    " should be the MTU to set.");
	}

	/* We have a static number of arguments. Therefore we can do it simple. */
	ifname = strdup(argv[1]);
	mtu = (int)strtol(argv[2], &ptr, 10);

	printf("Interface name: %s\n", ifname);
	printf("New MTU: %d", mtu);

	lifh = ifconfig_open();
	if (lifh == NULL) {
		errx(ENOMEM, "Failed to open libifconfig handle.");
		return (-1);
	}

	if (ifconfig_set_mtu(lifh, ifname, mtu) == 0) {
		printf("Successfully changed MTU of %s to %d\n", ifname, mtu);
		ifconfig_close(lifh);
		lifh = NULL;
		free(ifname);
		return (0);
	}

	switch (ifconfig_err_errtype(lifh)) {
	case SOCKET:
		warnx("couldn't create socket. This shouldn't happen.\n");
		break;
	case IOCTL:
		if (ifconfig_err_ioctlreq(lifh) == SIOCSIFMTU) {
			warnx("Failed to set MTU (SIOCSIFMTU)\n");
		} else {
			warnx(
				"Failed to set MTU due to error in unexpected ioctl() call %lu. Error code: %i.\n",
				ifconfig_err_ioctlreq(lifh),
				ifconfig_err_errno(lifh));
		}
		break;
	default:
		warnx(
			"Should basically never end up here in this example.\n");
		break;
	}

	ifconfig_close(lifh);
	lifh = NULL;
	free(ifname);
	return (-1);
}