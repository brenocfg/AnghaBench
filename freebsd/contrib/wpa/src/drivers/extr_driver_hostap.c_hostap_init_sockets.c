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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_ll {int /*<<< orphan*/  sll_ifindex; int /*<<< orphan*/  ifr_ifindex; int /*<<< orphan*/  sll_family; int /*<<< orphan*/  ifr_name; } ;
struct sockaddr {int dummy; } ;
struct ifreq {int /*<<< orphan*/  sll_ifindex; int /*<<< orphan*/  ifr_ifindex; int /*<<< orphan*/  sll_family; int /*<<< orphan*/  ifr_name; } ;
struct hostap_driver_data {scalar_t__ sock; int /*<<< orphan*/  iface; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int /*<<< orphan*/  SIOCGIFINDEX ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ eloop_register_read_sock (scalar_t__,int /*<<< orphan*/ ,struct hostap_driver_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  handle_read ; 
 scalar_t__ hostap_set_iface_flags (struct hostap_driver_data*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,struct sockaddr_ll*) ; 
 int linux_get_ifhwaddr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sockaddr_ll*,int /*<<< orphan*/ ,int) ; 
 int os_snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int hostap_init_sockets(struct hostap_driver_data *drv, u8 *own_addr)
{
	struct ifreq ifr;
	struct sockaddr_ll addr;

	drv->sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (drv->sock < 0) {
		wpa_printf(MSG_ERROR, "socket[PF_PACKET,SOCK_RAW]: %s",
			   strerror(errno));
		return -1;
	}

	if (eloop_register_read_sock(drv->sock, handle_read, drv, NULL)) {
		wpa_printf(MSG_ERROR, "Could not register read socket");
		return -1;
	}

        memset(&ifr, 0, sizeof(ifr));
	if (os_snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%sap",
			drv->iface) >= (int) sizeof(ifr.ifr_name)) {
		wpa_printf(MSG_ERROR, "hostap: AP interface name truncated");
		return -1;
	}
        if (ioctl(drv->sock, SIOCGIFINDEX, &ifr) != 0) {
		wpa_printf(MSG_ERROR, "ioctl(SIOCGIFINDEX): %s",
			   strerror(errno));
		return -1;
        }

	if (hostap_set_iface_flags(drv, 1)) {
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sll_family = AF_PACKET;
	addr.sll_ifindex = ifr.ifr_ifindex;
	wpa_printf(MSG_DEBUG, "Opening raw packet socket for ifindex %d",
		   addr.sll_ifindex);

	if (bind(drv->sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		wpa_printf(MSG_ERROR, "bind: %s", strerror(errno));
		return -1;
	}

	return linux_get_ifhwaddr(drv->sock, drv->iface, own_addr);
}