#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_raw {int /*<<< orphan*/  sr_ifname; } ;
struct TYPE_2__ {int /*<<< orphan*/  sa_data; } ;
struct ifreq {TYPE_1__ ifr_addr; int /*<<< orphan*/  ifr_name; } ;
struct ether_header {int /*<<< orphan*/  ether_shost; } ;
typedef  int /*<<< orphan*/  sr ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIFADDR ; 
 int getsockname (int,struct sockaddr_raw*,int*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int write (int,char*,int) ; 

int	sendip(int fd, char *pkt, int len)
{
	struct sockaddr_raw sr;
	int srlen = sizeof(sr);
	struct ifreq ifr;
	struct ether_header *eh = (struct ether_header *)pkt;

	if (getsockname(fd, &sr, &srlen) == -1)
	    {
		perror("getsockname");
		return -1;
	    }

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, sr.sr_ifname, sizeof ifr.ifr_name);

	if (ioctl(fd, SIOCGIFADDR, &ifr) == -1)
	    {
		perror("ioctl SIOCGIFADDR");
		return -1;
	    }

	memcpy(eh->ether_shost, ifr.ifr_addr.sa_data, sizeof(eh->ether_shost));

	if (write(fd, pkt, len) == -1)
	    {
		perror("send");
		return -1;
	    }

	return len;
}