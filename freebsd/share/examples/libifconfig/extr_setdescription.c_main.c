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
#define  SOCKET 128 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ifconfig_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifconfig_err_errno (int /*<<< orphan*/ *) ; 
 int ifconfig_err_errtype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifconfig_err_ioctlreq (int /*<<< orphan*/ *) ; 
 scalar_t__ ifconfig_get_description (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/ * ifconfig_open () ; 
 scalar_t__ ifconfig_set_description (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strdup (char*) ; 

int
main(int argc, char *argv[])
{
	char *ifname, *ifdescr, *curdescr;
	ifconfig_handle_t *lifh;

	if (argc != 3) {
		errx(EINVAL, "Invalid number of arguments."
		    " First argument should be interface name, second argument"
		    " should be the description to set.");
	}

	/* We have a static number of arguments. Therefore we can do it simple. */
	ifname = strdup(argv[1]);
	ifdescr = strdup(argv[2]);
	curdescr = NULL;

	printf("Interface name: %s\n", ifname);

	lifh = ifconfig_open();
	if (lifh == NULL) {
		errx(ENOMEM, "Failed to open libifconfig handle.");
		return (-1);
	}

	if (ifconfig_get_description(lifh, ifname, &curdescr) == 0) {
		printf("Old description: %s\n", curdescr);
	}

	printf("New description: %s\n\n", ifdescr);

	if (ifconfig_set_description(lifh, ifname, ifdescr) == 0) {
		printf("New description successfully set.\n");
	} else {
		switch (ifconfig_err_errtype(lifh)) {
		case SOCKET:
			err(ifconfig_err_errno(lifh), "Socket error");
			break;
		case IOCTL:
			err(ifconfig_err_errno(
				    lifh), "IOCTL(%lu) error",
			    ifconfig_err_ioctlreq(lifh));
			break;
		default:
			err(ifconfig_err_errno(lifh), "Other error");
			break;
		}
	}

	free(ifname);
	free(ifdescr);
	free(curdescr);
	ifname = NULL;
	ifdescr = NULL;
	curdescr = NULL;

	ifconfig_close(lifh);
	return (0);
}