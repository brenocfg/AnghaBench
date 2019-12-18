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
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; void* sin_family; } ;
struct ifaliasreq {int /*<<< orphan*/  ifra_mask; int /*<<< orphan*/  ifra_addr; int /*<<< orphan*/  ifra_name; } ;
typedef  int /*<<< orphan*/  ifra ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCAIFADDR ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  bzero (struct ifaliasreq*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 void* inet_addr (char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifaliasreq*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int
ifconfig_inet(char *ifname, int ifunit, char *ip, char *netmask)
{
	struct sockaddr_in *sinp;
	struct ifaliasreq ifra;
	int s;

	s = socket(PF_INET, SOCK_RAW, 0);
	if (s < 0) {
		warn("ifconfig_inet: socket(PF_INET, SOCK_RAW, 0)");
		return (-1);
	}

	bzero(&ifra, sizeof(ifra));
	snprintf(ifra.ifra_name, sizeof(ifra.ifra_name), "%s%d", ifname,
	    ifunit);

	sinp = (struct sockaddr_in *)&ifra.ifra_addr;
	sinp->sin_family = AF_INET;
	sinp->sin_len = sizeof(ifra.ifra_addr);
	sinp->sin_addr.s_addr = inet_addr(ip);

	sinp = (struct sockaddr_in *)&ifra.ifra_mask;
	sinp->sin_family = AF_INET;
	sinp->sin_len = sizeof(ifra.ifra_addr);
	sinp->sin_addr.s_addr = inet_addr(netmask);

	if (ioctl(s, SIOCAIFADDR, &ifra) < 0) {
		warn("ifconfig_inet: ioctl(%s%d, SIOCAIFADDR, %s)", ifname,
		    ifunit, ip);
		close(s);
		return (-1);
	}

	close(s);
	return (0);
}