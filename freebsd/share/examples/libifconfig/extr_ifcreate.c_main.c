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
 int /*<<< orphan*/  SIOCIFCREATE2 ; 
#define  SOCKET 128 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ifconfig_close (int /*<<< orphan*/ *) ; 
 scalar_t__ ifconfig_create_interface (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  ifconfig_err_errno (int /*<<< orphan*/ *) ; 
 int ifconfig_err_errtype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifconfig_err_ioctlreq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ifconfig_open () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char *argv[])
{
	char *ifname, *ifactualname;
	ifconfig_handle_t *lifh;

	if (argc != 2) {
		errx(EINVAL, "Invalid number of arguments."
		    " Only one argument is accepted, and it should be the name"
		    " of the interface to be created.");
	}

	/* We have a static number of arguments. Therefore we can do it simple. */
	ifname = strdup(argv[1]);

	printf("Requested interface name: %s\n", ifname);

	lifh = ifconfig_open();
	if (lifh == NULL) {
		errx(ENOMEM, "Failed to open libifconfig handle.");
		return (-1);
	}

	if (ifconfig_create_interface(lifh, ifname, &ifactualname) == 0) {
		printf("Successfully created interface '%s'\n", ifactualname);
		ifconfig_close(lifh);
		lifh = NULL;
		free(ifname);
		free(ifactualname);
		return (0);
	}

	switch (ifconfig_err_errtype(lifh)) {
	case SOCKET:
		warnx("couldn't create socket. This shouldn't happen.\n");
		break;
	case IOCTL:
		if (ifconfig_err_ioctlreq(lifh) == SIOCIFCREATE2) {
			warnx(
				"Failed to create interface (SIOCIFCREATE2)\n");
		}
		break;
	default:
		warnx(
			"This is a thorough example accommodating for temporary"
			" 'not implemented yet' errors. That's likely what happened"
			" now. If not, your guess is as good as mine. ;)"
			" Error code: %d\n", ifconfig_err_errno(
				lifh));
		break;
	}

	ifconfig_close(lifh);
	lifh = NULL;
	free(ifname);
	free(ifactualname);
	return (-1);
}