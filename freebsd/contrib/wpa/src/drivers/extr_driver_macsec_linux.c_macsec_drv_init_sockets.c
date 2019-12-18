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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct sockaddr_ll {scalar_t__ sll_ifindex; scalar_t__ ifr_ifindex; TYPE_2__ ifr_hwaddr; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  sll_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_3__ {scalar_t__ sock; int /*<<< orphan*/  ifname; int /*<<< orphan*/  ctx; } ;
struct macsec_drv_data {TYPE_1__ common; } ;
struct ifreq {scalar_t__ sll_ifindex; scalar_t__ ifr_ifindex; TYPE_2__ ifr_hwaddr; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  sll_family; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_PAE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int /*<<< orphan*/  SIOCGIFHWADDR ; 
 int /*<<< orphan*/  SIOCGIFINDEX ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ eloop_register_read_sock (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,struct sockaddr_ll*) ; 
 int /*<<< orphan*/  macsec_drv_handle_read ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_ll*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pae_group_addr ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ wired_multicast_membership (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int macsec_drv_init_sockets(struct macsec_drv_data *drv, u8 *own_addr)
{
#ifdef __linux__
	struct ifreq ifr;
	struct sockaddr_ll addr;

	drv->common.sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_PAE));
	if (drv->common.sock < 0) {
		wpa_printf(MSG_ERROR, "socket[PF_PACKET,SOCK_RAW]: %s",
			   strerror(errno));
		return -1;
	}

	if (eloop_register_read_sock(drv->common.sock, macsec_drv_handle_read,
				     drv->common.ctx, NULL)) {
		wpa_printf(MSG_INFO, "Could not register read socket");
		return -1;
	}

	os_memset(&ifr, 0, sizeof(ifr));
	os_strlcpy(ifr.ifr_name, drv->common.ifname, sizeof(ifr.ifr_name));
	if (ioctl(drv->common.sock, SIOCGIFINDEX, &ifr) != 0) {
		wpa_printf(MSG_ERROR, "ioctl(SIOCGIFINDEX): %s",
			   strerror(errno));
		return -1;
	}

	os_memset(&addr, 0, sizeof(addr));
	addr.sll_family = AF_PACKET;
	addr.sll_ifindex = ifr.ifr_ifindex;
	wpa_printf(MSG_DEBUG, "Opening raw packet socket for ifindex %d",
		   addr.sll_ifindex);

	if (bind(drv->common.sock, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		wpa_printf(MSG_ERROR, "bind: %s", strerror(errno));
		return -1;
	}

	/* filter multicast address */
	if (wired_multicast_membership(drv->common.sock, ifr.ifr_ifindex,
				       pae_group_addr, 1) < 0) {
		wpa_printf(MSG_ERROR, "wired: Failed to add multicast group "
			   "membership");
		return -1;
	}

	os_memset(&ifr, 0, sizeof(ifr));
	os_strlcpy(ifr.ifr_name, drv->common.ifname, sizeof(ifr.ifr_name));
	if (ioctl(drv->common.sock, SIOCGIFHWADDR, &ifr) != 0) {
		wpa_printf(MSG_ERROR, "ioctl(SIOCGIFHWADDR): %s",
			   strerror(errno));
		return -1;
	}

	if (ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER) {
		wpa_printf(MSG_INFO, "Invalid HW-addr family 0x%04x",
			   ifr.ifr_hwaddr.sa_family);
		return -1;
	}
	os_memcpy(own_addr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);

	return 0;
#else /* __linux__ */
	return -1;
#endif /* __linux__ */
}