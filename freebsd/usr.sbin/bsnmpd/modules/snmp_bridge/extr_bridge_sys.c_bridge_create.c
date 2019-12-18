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
struct ifreq {char* ifr_data; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  struct ifreq* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCIFCREATE ; 
 int /*<<< orphan*/  SIOCSIFNAME ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  sock ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

int
bridge_create(const char *b_name)
{
	char *new_name;
	struct ifreq ifr;

	bzero(&ifr, sizeof(ifr));
	strlcpy(ifr.ifr_name, b_name, sizeof(ifr.ifr_name));

	if (ioctl(sock, SIOCIFCREATE, &ifr) < 0) {
		syslog(LOG_ERR, "create bridge: ioctl(SIOCIFCREATE) "
		    "failed: %s", strerror(errno));
		return (-1);
	}

	if (strcmp(b_name, ifr.ifr_name) == 0)
		return (0);

	if ((new_name = strdup(b_name)) == NULL) {
		syslog(LOG_ERR, "create bridge: strdup() failed");
		return (-1);
	}

	ifr.ifr_data = new_name;
	if (ioctl(sock, SIOCSIFNAME, (caddr_t) &ifr) < 0) {
		syslog(LOG_ERR, "create bridge: ioctl(SIOCSIFNAME) "
		    "failed: %s", strerror(errno));
		free(new_name);
		return (-1);
	}

	return (0);
}