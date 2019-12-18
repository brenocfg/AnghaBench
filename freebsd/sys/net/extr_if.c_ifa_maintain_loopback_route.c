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
struct sockaddr_dl {int dummy; } ;
struct sockaddr {int dummy; } ;
struct rt_addrinfo {int rti_flags; struct sockaddr** rti_info; int /*<<< orphan*/ * rti_ifa; int /*<<< orphan*/ * rti_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_fib; int /*<<< orphan*/  if_type; } ;
struct ifaddr {int ifa_flags; int /*<<< orphan*/  ifa_addr; struct ifnet* ifa_ifp; } ;
struct epoch_tracker {int dummy; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 int RTF_HOST ; 
 int RTF_PINNED ; 
 int RTF_STATIC ; 
 int RTM_ADD ; 
 int RTM_DELETE ; 
 int /*<<< orphan*/ * V_loif ; 
 int /*<<< orphan*/  bzero (struct rt_addrinfo*,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,char const*,int) ; 
 int /*<<< orphan*/  ifa_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ifaof_ifpforaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_init_sdl (struct ifnet*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int rtrequest1_fib (int,struct rt_addrinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ifa_maintain_loopback_route(int cmd, const char *otype, struct ifaddr *ifa,
    struct sockaddr *ia)
{
	struct epoch_tracker et;
	int error;
	struct rt_addrinfo info;
	struct sockaddr_dl null_sdl;
	struct ifnet *ifp;

	ifp = ifa->ifa_ifp;

	bzero(&info, sizeof(info));
	if (cmd != RTM_DELETE)
		info.rti_ifp = V_loif;
	if (cmd == RTM_ADD) {
		/* explicitly specify (loopback) ifa */
		if (info.rti_ifp != NULL) {
			NET_EPOCH_ENTER(et);
			info.rti_ifa = ifaof_ifpforaddr(ifa->ifa_addr, info.rti_ifp);
			if (info.rti_ifa != NULL)
				ifa_ref(info.rti_ifa);
			NET_EPOCH_EXIT(et);
		}
	}
	info.rti_flags = ifa->ifa_flags | RTF_HOST | RTF_STATIC | RTF_PINNED;
	info.rti_info[RTAX_DST] = ia;
	info.rti_info[RTAX_GATEWAY] = (struct sockaddr *)&null_sdl;
	link_init_sdl(ifp, (struct sockaddr *)&null_sdl, ifp->if_type);

	error = rtrequest1_fib(cmd, &info, NULL, ifp->if_fib);

	if (error != 0 &&
	    !(cmd == RTM_ADD && error == EEXIST) &&
	    !(cmd == RTM_DELETE && error == ENOENT))
		if_printf(ifp, "%s failed: %d\n", otype, error);

	return (error);
}