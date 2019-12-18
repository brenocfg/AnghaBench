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
struct sockaddr_dl {scalar_t__ sdl_type; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; scalar_t__ ifa_addr; struct ifaddrs* ifa_next; } ;
struct ether_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IFT_ETHER ; 
 scalar_t__ LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  ether_ntoa (struct ether_addr*) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 int getifaddrs (struct ifaddrs**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
kvp_if_name_to_mac(char *if_name)
{
	char *mac_addr = NULL;
	struct ifaddrs *ifaddrs_ptr;
	struct ifaddrs *head_ifaddrs_ptr;
	struct sockaddr_dl *sdl;
	int status;

	status = getifaddrs(&ifaddrs_ptr);

	if (status >= 0) {
		head_ifaddrs_ptr = ifaddrs_ptr;
		do {
			sdl = (struct sockaddr_dl *)(uintptr_t)ifaddrs_ptr->ifa_addr;
			if ((sdl->sdl_type == IFT_ETHER) &&
			    (strcmp(ifaddrs_ptr->ifa_name, if_name) == 0)) {
				mac_addr = strdup(ether_ntoa((struct ether_addr *)(LLADDR(sdl))));
				break;
			}
		} while ((ifaddrs_ptr = ifaddrs_ptr->ifa_next) != NULL);
		freeifaddrs(head_ifaddrs_ptr);
	}

	return (mac_addr);
}