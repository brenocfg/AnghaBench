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
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct interface {int int_state; int int_if_flags; int /*<<< orphan*/  int_index; } ;
struct group_req {int /*<<< orphan*/  gr_group; int /*<<< orphan*/  gr_interface; } ;
typedef  int /*<<< orphan*/  gr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  INADDR_ALLHOSTS_GROUP ; 
 int /*<<< orphan*/  INADDR_ALLROUTERS_GROUP ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int IS_ALL_HOSTS ; 
 int IS_ALL_ROUTERS ; 
 int IS_NO_ADV_IN ; 
 int IS_NO_ADV_OUT ; 
 int IS_NO_RDISC ; 
 int /*<<< orphan*/  LOGERR (char*) ; 
 int /*<<< orphan*/  MCAST_JOIN_GROUP ; 
 int /*<<< orphan*/  MCAST_LEAVE_GROUP ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rdisc_sock () ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct group_req*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rdisc_sock ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct group_req*,int) ; 
 scalar_t__ supplier ; 

void
set_rdisc_mg(struct interface *ifp,
	     int on)			/* 0=turn it off */
{
	struct group_req gr;
	struct sockaddr_in *sin;

	assert(ifp != NULL);

	if (rdisc_sock < 0) {
		/* Create the raw socket so that we can hear at least
		 * broadcast router discovery packets.
		 */
		if ((ifp->int_state & IS_NO_RDISC) == IS_NO_RDISC
		    || !on)
			return;
		get_rdisc_sock();
	}

	if (!(ifp->int_if_flags & IFF_MULTICAST)) {
		ifp->int_state &= ~(IS_ALL_HOSTS | IS_ALL_ROUTERS);
		return;
	}

	memset(&gr, 0, sizeof(gr));
	gr.gr_interface = ifp->int_index;
	sin = (struct sockaddr_in *)&gr.gr_group;
	sin->sin_family = AF_INET;
#ifdef _HAVE_SIN_LEN
	sin->sin_len = sizeof(struct sockaddr_in);
#endif

	if (supplier
	    || (ifp->int_state & IS_NO_ADV_IN)
	    || !on) {
		/* stop listening to advertisements
		 */
		if (ifp->int_state & IS_ALL_HOSTS) {
			sin->sin_addr.s_addr = htonl(INADDR_ALLHOSTS_GROUP);
			if (setsockopt(rdisc_sock, IPPROTO_IP,
				       MCAST_LEAVE_GROUP,
				       &gr, sizeof(gr)) < 0)
				LOGERR("MCAST_LEAVE_GROUP ALLHOSTS");
			ifp->int_state &= ~IS_ALL_HOSTS;
		}

	} else if (!(ifp->int_state & IS_ALL_HOSTS)) {
		/* start listening to advertisements
		 */
		sin->sin_addr.s_addr = htonl(INADDR_ALLHOSTS_GROUP);
		if (setsockopt(rdisc_sock, IPPROTO_IP, MCAST_JOIN_GROUP,
			       &gr, sizeof(gr)) < 0) {
			LOGERR("MCAST_JOIN_GROUP ALLHOSTS");
		} else {
			ifp->int_state |= IS_ALL_HOSTS;
		}
	}

	if (!supplier
	    || (ifp->int_state & IS_NO_ADV_OUT)
	    || !on) {
		/* stop listening to solicitations
		 */
		if (ifp->int_state & IS_ALL_ROUTERS) {
			sin->sin_addr.s_addr = htonl(INADDR_ALLROUTERS_GROUP);
			if (setsockopt(rdisc_sock, IPPROTO_IP,
				       MCAST_LEAVE_GROUP,
				       &gr, sizeof(gr)) < 0)
				LOGERR("MCAST_LEAVE_GROUP ALLROUTERS");
			ifp->int_state &= ~IS_ALL_ROUTERS;
		}

	} else if (!(ifp->int_state & IS_ALL_ROUTERS)) {
		/* start hearing solicitations
		 */
		sin->sin_addr.s_addr = htonl(INADDR_ALLROUTERS_GROUP);
		if (setsockopt(rdisc_sock, IPPROTO_IP, MCAST_JOIN_GROUP,
			       &gr, sizeof(gr)) < 0) {
			LOGERR("MCAST_JOIN_GROUP ALLROUTERS");
		} else {
			ifp->int_state |= IS_ALL_ROUTERS;
		}
	}
}