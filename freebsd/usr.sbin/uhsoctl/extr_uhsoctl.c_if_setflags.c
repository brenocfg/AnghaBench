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
struct ifreq {int ifr_flags; int ifr_flagshigh; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
if_setflags(const char *ifnam, int flags)
{
	struct ifreq ifr;
	int fd, error;
	unsigned int oflags = 0;

	memset(&ifr, 0, sizeof(struct ifreq));
	strlcpy(ifr.ifr_name, ifnam, sizeof(ifr.ifr_name));

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
		return (-1);

	error = ioctl(fd, SIOCGIFFLAGS, &ifr);
	if (error == 0) {
		oflags = (ifr.ifr_flags & 0xffff)  | (ifr.ifr_flagshigh << 16);
	}

	if (flags < 0)
		oflags &= ~(-flags);
	else
		oflags |= flags;

	ifr.ifr_flags = oflags & 0xffff;
	ifr.ifr_flagshigh = oflags >> 16;

	error = ioctl(fd, SIOCSIFFLAGS, &ifr);
	if (error != 0)
		warn("ioctl SIOCSIFFLAGS");

	close(fd);
	return (error);
}