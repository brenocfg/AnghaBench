#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec {scalar_t__ tv_sec; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {scalar_t__ ia6t_expire; scalar_t__ ia6t_preferred; } ;
struct ifconfig_inet6_addr {int prefixlen; int flags; int vhid; TYPE_2__ lifetime; TYPE_1__* sin6; int /*<<< orphan*/ * dstin6; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; } ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;
typedef  int /*<<< orphan*/  addr_buf ;
struct TYPE_3__ {int sin6_scope_id; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC_FAST ; 
 int IN6_IFF_ANYCAST ; 
 int IN6_IFF_AUTOCONF ; 
 int IN6_IFF_DEPRECATED ; 
 int IN6_IFF_DETACHED ; 
 int IN6_IFF_DUPLICATED ; 
 int IN6_IFF_PREFER_SOURCE ; 
 int IN6_IFF_TEMPORARY ; 
 int IN6_IFF_TENTATIVE ; 
 int /*<<< orphan*/  MAX (long,scalar_t__) ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ifconfig_inet6_get_addrinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ifaddrs*,struct ifconfig_inet6_addr*) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_inet6_addr(ifconfig_handle_t *lifh, struct ifaddrs *ifa)
{
	struct ifconfig_inet6_addr addr;
	char addr_buf[NI_MAXHOST];
	struct timespec now;

	/* Print the address */
	if (ifconfig_inet6_get_addrinfo(lifh, ifa->ifa_name, ifa, &addr) != 0) {
		err(1, "ifconfig_inet6_get_addrinfo");
	}
	if (0 != getnameinfo((struct sockaddr *)addr.sin6, addr.sin6->sin6_len,
	    addr_buf, sizeof(addr_buf), NULL, 0, NI_NUMERICHOST)) {
		inet_ntop(AF_INET6, &addr.sin6->sin6_addr, addr_buf,
		    sizeof(addr_buf));
	}
	printf("\tinet6 %s", addr_buf);

	if (addr.dstin6) {
		inet_ntop(AF_INET6, addr.dstin6, addr_buf, sizeof(addr_buf));
		printf(" --> %s", addr_buf);
	}

	/* Print the netmask */
	printf(" prefixlen %d ", addr.prefixlen);

	/* Print the scopeid*/
	if (addr.sin6->sin6_scope_id) {
		printf("scopeid 0x%x ", addr.sin6->sin6_scope_id);
	}

	/* Print the flags */
	if ((addr.flags & IN6_IFF_ANYCAST) != 0) {
		printf("anycast ");
	}
	if ((addr.flags & IN6_IFF_TENTATIVE) != 0) {
		printf("tentative ");
	}
	if ((addr.flags & IN6_IFF_DUPLICATED) != 0) {
		printf("duplicated ");
	}
	if ((addr.flags & IN6_IFF_DETACHED) != 0) {
		printf("detached ");
	}
	if ((addr.flags & IN6_IFF_DEPRECATED) != 0) {
		printf("deprecated ");
	}
	if ((addr.flags & IN6_IFF_AUTOCONF) != 0) {
		printf("autoconf ");
	}
	if ((addr.flags & IN6_IFF_TEMPORARY) != 0) {
		printf("temporary ");
	}
	if ((addr.flags & IN6_IFF_PREFER_SOURCE) != 0) {
		printf("prefer_source ");
	}

	/* Print the lifetimes */
	clock_gettime(CLOCK_MONOTONIC_FAST, &now);
	if (addr.lifetime.ia6t_preferred || addr.lifetime.ia6t_expire) {
		printf("pltime ");
		if (addr.lifetime.ia6t_preferred) {
			printf("%ld ", MAX(0l,
			    addr.lifetime.ia6t_preferred - now.tv_sec));
		} else {
			printf("infty ");
		}

		printf("vltime ");
		if (addr.lifetime.ia6t_expire) {
			printf("%ld ", MAX(0l,
			    addr.lifetime.ia6t_expire - now.tv_sec));
		} else {
			printf("infty ");
		}
	}

	/* Print the vhid */
	if (addr.vhid != 0) {
		printf("vhid %d ", addr.vhid);
	}
	printf("\n");
}