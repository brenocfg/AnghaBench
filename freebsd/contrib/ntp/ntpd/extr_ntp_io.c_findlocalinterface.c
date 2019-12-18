#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  sa; } ;
typedef  TYPE_1__ sockaddr_u ;
typedef  int /*<<< orphan*/  saddr ;
typedef  int /*<<< orphan*/  on ;
struct TYPE_13__ {scalar_t__ ignore_packets; } ;
typedef  TYPE_2__ endpt ;
typedef  scalar_t__ SOCKET ;
typedef  int GETSOCKNAME_SOCKLEN_TYPE ;

/* Variables and functions */
 scalar_t__ AF (TYPE_1__*) ; 
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int INT_LOOPBACK ; 
 scalar_t__ INVALID_SOCKET ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCKLEN (TYPE_1__*) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int connect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* findclosestinterface (TYPE_1__*,int) ; 
 TYPE_2__* getinterface (TYPE_1__*,int) ; 
 int getsockname (scalar_t__,int /*<<< orphan*/ *,int*) ; 
 int setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoa (TYPE_1__*) ; 

__attribute__((used)) static endpt *
findlocalinterface(
	sockaddr_u *	addr,
	int		flags,
	int		bcast
	)
{
	GETSOCKNAME_SOCKLEN_TYPE	sockaddrlen;
	endpt *				iface;
	sockaddr_u			saddr;
	SOCKET				s;
	int				rtn;
	int				on;

	DPRINTF(4, ("Finding interface for addr %s in list of addresses\n",
		    stoa(addr)));

	/* [Bug 3437] The dummy POOL peer comes in with an AF of
	 * zero. This is bound to fail, but on the way to nowhere it
	 * triggers a security incident on SELinux.
	 *
	 * Checking the condition and failing early is probably a good
	 * advice, and even saves us some syscalls in that case.
	 * Thanks to Miroslav Lichvar for finding this.
	 */
	if (AF_UNSPEC == AF(addr))
		return NULL;

	s = socket(AF(addr), SOCK_DGRAM, 0);
	if (INVALID_SOCKET == s)
		return NULL;

	/*
	 * If we are looking for broadcast interface we need to set this
	 * socket to allow broadcast
	 */
	if (bcast) {
		on = 1;
		if (SOCKET_ERROR == setsockopt(s, SOL_SOCKET,
						SO_BROADCAST,
						(void *)&on,
						sizeof(on))) {
			closesocket(s);
			return NULL;
		}
	}

	rtn = connect(s, &addr->sa, SOCKLEN(addr));
	if (SOCKET_ERROR == rtn) {
		closesocket(s);
		return NULL;
	}

	sockaddrlen = sizeof(saddr);
	rtn = getsockname(s, &saddr.sa, &sockaddrlen);
	closesocket(s);
	if (SOCKET_ERROR == rtn)
		return NULL;

	DPRINTF(4, ("findlocalinterface: kernel maps %s to %s\n",
		    stoa(addr), stoa(&saddr)));

	iface = getinterface(&saddr, flags);

	/*
	 * if we didn't find an exact match on saddr, find the closest
	 * available local address.  This handles the case of the
	 * address suggested by the kernel being excluded by nic rules
	 * or the user's -I and -L options to ntpd.
	 * See http://bugs.ntp.org/1184 and http://bugs.ntp.org/1683
	 * for more background.
	 */
	if (NULL == iface || iface->ignore_packets)
		iface = findclosestinterface(&saddr,
					     flags | INT_LOOPBACK);

	/* Don't use an interface which will ignore replies */
	if (iface != NULL && iface->ignore_packets)
		iface = NULL;

	return iface;
}