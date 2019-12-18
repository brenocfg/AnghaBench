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
struct timespec {scalar_t__ tv_sec; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr_dl {scalar_t__ sdl_alen; int sdl_type; int sdl_nlen; scalar_t__ sdl_index; } ;
struct TYPE_2__ {scalar_t__ rmx_expire; } ;
struct rt_msghdr {int rtm_flags; TYPE_1__ rtm_rmx; } ;
struct if_nameindex {scalar_t__ if_index; scalar_t__ if_name; } ;
struct hostent {char* h_name; } ;
struct ether_addr {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ ETHER_ADDR_LEN ; 
#define  IFT_ATM 134 
#define  IFT_BRIDGE 133 
#define  IFT_ETHER 132 
#define  IFT_FDDI 131 
#define  IFT_IEEE1394 130 
#define  IFT_INFINIBAND 129 
#define  IFT_L2VLAN 128 
 scalar_t__ LLADDR (struct sockaddr_dl*) ; 
 int RTF_ANNOUNCE ; 
 scalar_t__ TRY_AGAIN ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  ether_ntoa (struct ether_addr*) ; 
 scalar_t__ expire_time ; 
 struct hostent* gethostbyaddr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ h_errno ; 
 struct if_nameindex* if_nameindex () ; 
 struct if_nameindex* ifnameindex ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_ntoa (struct sockaddr_dl*) ; 
 int nflag ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 

__attribute__((used)) static void
print_entry(struct sockaddr_dl *sdl,
	struct sockaddr_in *addr, struct rt_msghdr *rtm)
{
	const char *host;
	struct hostent *hp;
	struct if_nameindex *p;

	if (ifnameindex == NULL)
		if ((ifnameindex = if_nameindex()) == NULL)
			xo_err(1, "cannot retrieve interface names");

	xo_open_instance("arp-cache");

	if (nflag == 0)
		hp = gethostbyaddr((caddr_t)&(addr->sin_addr),
		    sizeof addr->sin_addr, AF_INET);
	else
		hp = 0;
	if (hp)
		host = hp->h_name;
	else {
		host = "?";
		if (h_errno == TRY_AGAIN)
			nflag = 1;
	}
	xo_emit("{:hostname/%s} ({:ip-address/%s}) at ", host,
	    inet_ntoa(addr->sin_addr));
	if (sdl->sdl_alen) {
		if ((sdl->sdl_type == IFT_ETHER ||
		    sdl->sdl_type == IFT_L2VLAN ||
		    sdl->sdl_type == IFT_BRIDGE) &&
		    sdl->sdl_alen == ETHER_ADDR_LEN)
			xo_emit("{:mac-address/%s}",
			    ether_ntoa((struct ether_addr *)LLADDR(sdl)));
		else {
			int n = sdl->sdl_nlen > 0 ? sdl->sdl_nlen + 1 : 0;

			xo_emit("{:mac-address/%s}", link_ntoa(sdl) + n);
		}
	} else
		xo_emit("{d:/(incomplete)}{en:incomplete/true}");

	for (p = ifnameindex; p && ifnameindex->if_index &&
	    ifnameindex->if_name; p++) {
		if (p->if_index == sdl->sdl_index) {
			xo_emit(" on {:interface/%s}", p->if_name);
			break;
		}
	}

	if (rtm->rtm_rmx.rmx_expire == 0)
		xo_emit("{d:/ permanent}{en:permanent/true}");
	else {
		static struct timespec tp;
		if (tp.tv_sec == 0)
			clock_gettime(CLOCK_MONOTONIC, &tp);
		if ((expire_time = rtm->rtm_rmx.rmx_expire - tp.tv_sec) > 0)
			xo_emit(" expires in {:expires/%d} seconds",
			    (int)expire_time);
		else
			xo_emit("{d:/ expired}{en:expired/true}");
	}

	if (rtm->rtm_flags & RTF_ANNOUNCE)
		xo_emit("{d:/ published}{en:published/true}");

	switch(sdl->sdl_type) {
	case IFT_ETHER:
		xo_emit(" [{:type/ethernet}]");
		break;
	case IFT_FDDI:
		xo_emit(" [{:type/fddi}]");
		break;
	case IFT_ATM:
		xo_emit(" [{:type/atm}]");
		break;
	case IFT_L2VLAN:
		xo_emit(" [{:type/vlan}]");
		break;
	case IFT_IEEE1394:
		xo_emit(" [{:type/firewire}]");
		break;
	case IFT_BRIDGE:
		xo_emit(" [{:type/bridge}]");
		break;
	case IFT_INFINIBAND:
		xo_emit(" [{:type/infiniband}]");
		break;
	default:
		break;
	}

	xo_emit("\n");

	xo_close_instance("arp-cache");
}