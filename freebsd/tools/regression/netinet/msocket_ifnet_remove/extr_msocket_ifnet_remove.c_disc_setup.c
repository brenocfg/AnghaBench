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
struct ifreq {int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 char* DISC_IFNAME ; 
 int /*<<< orphan*/  DISC_IFUNIT ; 
#define  EEXIST 128 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCIFCREATE ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 scalar_t__ kldload (char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int
disc_setup(void)
{
	struct ifreq ifr;
	int s;

	if (kldload("if_disc") < 0) {
		switch (errno) {
		case EEXIST:
			break;
		default:
			warn("disc_setup: kldload(if_disc)");
			return (-1);
		}
	}

	s = socket(PF_INET, SOCK_RAW, 0);
	if (s < 0) {
		warn("disc_setup: socket(PF_INET, SOCK_RAW, 0)");
		return (-1);
	}

	bzero(&ifr, sizeof(ifr));
	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s%d", DISC_IFNAME,
	    DISC_IFUNIT);

	if (ioctl(s, SIOCIFCREATE, &ifr) < 0) {
		warn("disc_setup: ioctl(%s, SIOCIFCREATE)", ifr.ifr_name);
		close(s);
		return (-1);
	}

	close(s);
	return (0);
}