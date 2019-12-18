#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ifconfig_inet_addr {int vhid; TYPE_5__* broadcast; TYPE_4__* netmask; TYPE_2__* dst; TYPE_1__* sin; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; } ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;
typedef  int /*<<< orphan*/  addr_buf ;
struct TYPE_12__ {scalar_t__ s_addr; } ;
struct TYPE_11__ {TYPE_6__ sin_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_10__ {TYPE_3__ sin_addr; } ;
struct TYPE_8__ {TYPE_6__ sin_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int NI_MAXHOST ; 
 scalar_t__ ifconfig_inet_get_addrinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ifaddrs*,struct ifconfig_inet_addr*) ; 
 char* inet_ntoa (TYPE_6__) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_inet4_addr(ifconfig_handle_t *lifh, struct ifaddrs *ifa)
{
	struct ifconfig_inet_addr addr;
	char addr_buf[NI_MAXHOST];

	if (ifconfig_inet_get_addrinfo(lifh, ifa->ifa_name, ifa, &addr) != 0) {
		return;
	}

	inet_ntop(AF_INET, &addr.sin->sin_addr, addr_buf, sizeof(addr_buf));
	printf("\tinet %s", addr_buf);

	if (addr.dst) {
		printf(" --> %s", inet_ntoa(addr.dst->sin_addr));
	}

	printf(" netmask 0x%x ", ntohl(addr.netmask->sin_addr.s_addr));

	if ((addr.broadcast != NULL) &&
	    (addr.broadcast->sin_addr.s_addr != 0)) {
		printf("broadcast %s ", inet_ntoa(addr.broadcast->sin_addr));
	}

	if (addr.vhid != 0) {
		printf("vhid %d ", addr.vhid);
	}
	printf("\n");
}