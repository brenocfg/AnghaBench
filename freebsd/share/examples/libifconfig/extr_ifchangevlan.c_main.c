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
 int /*<<< orphan*/  SIOCGETVLAN ; 
 int /*<<< orphan*/  SIOCSETVLAN ; 
#define  SOCKET 128 
 int /*<<< orphan*/  USHRT_MAX ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ifconfig_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifconfig_err_errno (int /*<<< orphan*/ *) ; 
 int ifconfig_err_errtype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifconfig_err_ioctlreq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ifconfig_open () ; 
 scalar_t__ ifconfig_set_vlantag (int /*<<< orphan*/ *,char*,char*,unsigned short) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strdup (char*) ; 
 unsigned short strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char *argv[])
{
	char *ifname, *parentif;
	unsigned short vlantag;
	const char *errstr;
	ifconfig_handle_t *lifh;

	if (argc != 4) {
		errx(EINVAL, "Invalid number of arguments."
		    " Should provide exactly three arguments: "
		    "INTERFACE, PARENT_INTERFACE and VLAN_TAG.");
	}

	/* We have a static number of arguments. Therefore we can do it simple. */
	ifname = strdup(argv[1]);
	parentif = strdup(argv[2]);
	vlantag = strtonum(argv[3], 0, USHRT_MAX, &errstr);

	if (errstr != NULL) {
		errx(1, "VLAN_TAG must be between 0 and %i.\n", USHRT_MAX);
	}

	printf("Interface: %s\nNew VLAN tag: %i\n", ifname, vlantag);

	lifh = ifconfig_open();
	if (lifh == NULL) {
		errx(ENOMEM, "Failed to open libifconfig handle.");
		return (-1);
	}

	if (ifconfig_set_vlantag(lifh, ifname, parentif, vlantag) == 0) {
		printf("Successfully changed vlan tag.\n");
		ifconfig_close(lifh);
		lifh = NULL;
		free(ifname);
		free(parentif);
		return (0);
	}

	switch (ifconfig_err_errtype(lifh)) {
	case SOCKET:
		warnx("couldn't create socket. This shouldn't happen.\n");
		break;
	case IOCTL:
		if (ifconfig_err_ioctlreq(lifh) == SIOCGETVLAN) {
			warnx("Target interface isn't a VLAN interface.\n");
		}
		if (ifconfig_err_ioctlreq(lifh) == SIOCSETVLAN) {
			warnx(
				"Couldn't change VLAN properties of interface.\n");
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
	free(parentif);
	return (-1);
}