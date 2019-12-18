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
typedef  scalar_t__ u_int16_t ;
struct ifreq {scalar_t__ ifr_mtu; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  struct ifreq* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SIOCGIFMTU ; 
 int /*<<< orphan*/  SIOCSIFMTU ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warning (char*,scalar_t__,int /*<<< orphan*/ ) ; 

void
interface_set_mtu_priv(char *ifname, u_int16_t mtu)
{
	struct ifreq ifr;
	int sock;
	u_int16_t old_mtu;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		error("Can't create socket");

	memset(&ifr, 0, sizeof(ifr));
	old_mtu = 0;

	strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));

	if (ioctl(sock, SIOCGIFMTU, (caddr_t)&ifr) == -1)
		warning("SIOCGIFMTU failed (%s): %s", ifname,
			strerror(errno));
	else
		old_mtu = ifr.ifr_mtu;

	if (mtu != old_mtu) {
		ifr.ifr_mtu = mtu;

		if (ioctl(sock, SIOCSIFMTU, &ifr) == -1)
			warning("SIOCSIFMTU failed (%d): %s", mtu,
				strerror(errno));
	}

	close(sock);
}