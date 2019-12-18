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
 int /*<<< orphan*/  SIOCIFDESTROY ; 
#define  SOCKET 128 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ifconfig_close (int /*<<< orphan*/ *) ; 
 scalar_t__ ifconfig_destroy_interface (int /*<<< orphan*/ *,char*) ; 
 int ifconfig_err_errtype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifconfig_err_ioctlreq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ifconfig_open () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	char *ifname;
	ifconfig_handle_t *lifh;

	if (argc != 2) {
		errx(EINVAL, "Invalid number of arguments."
		    " Only one argument is accepted, and it should be the name"
		    " of the interface to be destroyed.");
	}

	/* We have a static number of arguments. Therefore we can do it simple. */
	ifname = strdup(argv[1]);

	printf("Interface name: %s\n", ifname);

	lifh = ifconfig_open();
	if (lifh == NULL) {
		errx(ENOMEM, "Failed to open libifconfig handle.");
		return (-1);
	}

	if (ifconfig_destroy_interface(lifh, ifname) == 0) {
		printf("Successfully destroyed interface '%s'.", ifname);
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
		if (ifconfig_err_ioctlreq(lifh) == SIOCIFDESTROY) {
			warnx(
				"Failed to destroy interface (SIOCIFDESTROY)\n");
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