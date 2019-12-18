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
struct ifmediareq {int ifm_status; int ifm_active; int /*<<< orphan*/  ifm_name; } ;
typedef  int /*<<< orphan*/  ifmr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINVAL ; 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
#define  IFM_ETHER 129 
#define  IFM_IEEE80211 128 
 int IFM_NMASK ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  cap_syslog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  capsyslog ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifmediareq*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int
interface_link_status(char *ifname)
{
	struct ifmediareq ifmr;
	int sock;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		error("Can't create socket");

	memset(&ifmr, 0, sizeof(ifmr));
	strlcpy(ifmr.ifm_name, ifname, sizeof(ifmr.ifm_name));
	if (ioctl(sock, SIOCGIFMEDIA, (caddr_t)&ifmr) == -1) {
		/* EINVAL -> link state unknown. treat as active */
		if (errno != EINVAL)
			cap_syslog(capsyslog, LOG_DEBUG,
			    "ioctl(SIOCGIFMEDIA) on %s: %m", ifname);
		close(sock);
		return (1);
	}
	close(sock);

	if (ifmr.ifm_status & IFM_AVALID) {
		switch (ifmr.ifm_active & IFM_NMASK) {
		case IFM_ETHER:
		case IFM_IEEE80211:
			if (ifmr.ifm_status & IFM_ACTIVE)
				return (1);
			else
				return (0);
		}
	}
	return (1);
}