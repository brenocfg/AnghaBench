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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; int sin_len; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct rip {int dummy; } ;
struct ip_mreqn {int /*<<< orphan*/  imr_ifindex; } ;
struct interface {int int_rip_sock; int int_if_flags; int int_state; char* int_name; int /*<<< orphan*/  int_index; } ;
typedef  int /*<<< orphan*/  osin ;
typedef  int /*<<< orphan*/  mreqn ;
typedef  enum output_type { ____Placeholder_output_type } output_type ;

/* Variables and functions */
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  INADDR_RIP_GROUP ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_MULTICAST_IF ; 
 int IS_BROKE ; 
 int IS_DUP ; 
 int /*<<< orphan*/  LOGERR (char*) ; 
 int MSG_DONTROUTE ; 
#define  NO_OUT_MULTICAST 133 
#define  NO_OUT_RIPV2 132 
#define  OUT_BROADCAST 131 
#define  OUT_MULTICAST 130 
#define  OUT_QUERY 129 
#define  OUT_UNICAST 128 
 int /*<<< orphan*/  RIP_PORT ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_1__) ; 
 int /*<<< orphan*/  memset (struct ip_mreqn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msglog (char*,char const*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int rip_sock ; 
 struct interface* rip_sock_mcast ; 
 int sendto (int,struct rip*,int,int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_mreqn*,int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  trace_act (char*,char*) ; 
 int /*<<< orphan*/  trace_rip (char const*,char*,struct sockaddr_in*,struct interface*,struct rip*,int) ; 

int					/* <0 on failure */
output(enum output_type type,
       struct sockaddr_in *dst,		/* send to here */
       struct interface *ifp,
       struct rip *buf,
       int size)			/* this many bytes */
{
	struct sockaddr_in osin;
	int flags;
	const char *msg;
	int res;
	int soc;
	int serrno;

	assert(ifp != NULL);
	osin = *dst;
	if (osin.sin_port == 0)
		osin.sin_port = htons(RIP_PORT);
#ifdef _HAVE_SIN_LEN
	if (osin.sin_len == 0)
		osin.sin_len = sizeof(osin);
#endif

	soc = rip_sock;
	flags = 0;

	switch (type) {
	case OUT_QUERY:
		msg = "Answer Query";
		if (soc < 0)
			soc = ifp->int_rip_sock;
		break;
	case OUT_UNICAST:
		msg = "Send";
		if (soc < 0)
			soc = ifp->int_rip_sock;
		flags = MSG_DONTROUTE;
		break;
	case OUT_BROADCAST:
		if (ifp->int_if_flags & IFF_POINTOPOINT) {
			msg = "Send";
		} else {
			msg = "Send bcast";
		}
		flags = MSG_DONTROUTE;
		break;
	case OUT_MULTICAST:
		if ((ifp->int_if_flags & (IFF_POINTOPOINT|IFF_MULTICAST)) ==
		    IFF_POINTOPOINT) {
			msg = "Send pt-to-pt";
		} else if (ifp->int_state & IS_DUP) {
			trace_act("abort multicast output via %s"
				  " with duplicate address",
				  ifp->int_name);
			return 0;
		} else {
			msg = "Send mcast";
			if (rip_sock_mcast != ifp) {
				struct ip_mreqn mreqn;

				memset(&mreqn, 0, sizeof(struct ip_mreqn));
				mreqn.imr_ifindex = ifp->int_index;
				if (0 > setsockopt(rip_sock,
						   IPPROTO_IP,
						   IP_MULTICAST_IF,
						   &mreqn,
						   sizeof(mreqn))) {
					serrno = errno;
					LOGERR("setsockopt(rip_sock, "
					       "IP_MULTICAST_IF)");
					errno = serrno;
					ifp = NULL;
					return -1;
				}
				rip_sock_mcast = ifp;
			}
			osin.sin_addr.s_addr = htonl(INADDR_RIP_GROUP);
		}
		break;

	case NO_OUT_MULTICAST:
	case NO_OUT_RIPV2:
	default:
#ifdef DEBUG
		abort();
#endif
		return -1;
	}

	trace_rip(msg, "to", &osin, ifp, buf, size);

	res = sendto(soc, buf, size, flags,
		     (struct sockaddr *)&osin, sizeof(osin));
	if (res < 0
	    && (ifp == NULL || !(ifp->int_state & IS_BROKE))) {
		serrno = errno;
		msglog("%s sendto(%s%s%s.%d): %s", msg,
		       ifp != NULL ? ifp->int_name : "",
		       ifp != NULL ? ", " : "",
		       inet_ntoa(osin.sin_addr),
		       ntohs(osin.sin_port),
		       strerror(errno));
		errno = serrno;
	}

	return res;
}