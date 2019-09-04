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
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct ifaddrs {char* ifa_name; scalar_t__ ifa_netmask; TYPE_1__* ifa_addr; struct ifaddrs* ifa_next; } ;
struct TYPE_3__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  __builtin_clz (unsigned int) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,char*) ; 

unsigned get_my_ipv4 (void) {
  struct ifaddrs *ifa_first, *ifa;
  unsigned my_ip = 0, my_netmask = -1; 
  char *my_iface = 0;
  if (getifaddrs (&ifa_first) < 0) {
    perror ("getifaddrs()");
    return 0;
  }
  for (ifa = ifa_first; ifa; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr->sa_family != AF_INET) {
      continue;
    }
    if (!strncmp (ifa->ifa_name, "lo", 2)) {
      continue;
    }
    unsigned ip = ntohl (((struct sockaddr_in *) ifa->ifa_addr)->sin_addr.s_addr);
    unsigned mask = ntohl (((struct sockaddr_in *) ifa->ifa_netmask)->sin_addr.s_addr);
    // fprintf (stderr, "%08x %08x\t%s\n", ip, mask, ifa->ifa_name);
    if ((ip & (-1 << 24)) == (10 << 24) && mask < my_netmask) {
      my_ip = ip;
      my_netmask = mask;
      my_iface = ifa->ifa_name;
    }
  }
  vkprintf (1, "using main IP %d.%d.%d.%d/%d at interface %s\n", (my_ip >> 24), (my_ip >> 16) & 255, (my_ip >> 8) & 255, my_ip & 255,
	    __builtin_clz (~my_netmask), my_iface ?: "(none)"); 
  freeifaddrs (ifa_first);
  return my_ip;
}