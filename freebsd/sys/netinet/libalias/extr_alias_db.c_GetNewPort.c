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
typedef  void* u_short ;
struct libalias {int packetAliasMode; } ;
struct alias_link {int flags; void* alias_port; int /*<<< orphan*/  link_type; int /*<<< orphan*/  sockfd; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  alias_addr; int /*<<< orphan*/  dst_addr; void* src_port; } ;

/* Variables and functions */
 scalar_t__ ALIAS_PORT_BASE ; 
 int ALIAS_PORT_MASK ; 
 struct alias_link* FindLinkIn (struct libalias*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GET_ALIAS_PORT ; 
 int GET_NEW_PORT_MAX_ATTEMPTS ; 
 scalar_t__ GetSocket (struct libalias*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int LINK_PARTIALLY_SPECIFIED ; 
 int /*<<< orphan*/  LINK_TCP ; 
 int /*<<< orphan*/  LINK_UDP ; 
 int PKT_ALIAS_SAME_PORTS ; 
 int PKT_ALIAS_USE_SOCKETS ; 
 int arc4random () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 void* htons (void*) ; 
 void* ntohs (void*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
GetNewPort(struct libalias *la, struct alias_link *lnk, int alias_port_param)
{
	int i;
	int max_trials;
	u_short port_sys;
	u_short port_net;

	LIBALIAS_LOCK_ASSERT(la);
/*
   Description of alias_port_param for GetNewPort().  When
   this parameter is zero or positive, it precisely specifies
   the port number.  GetNewPort() will return this number
   without check that it is in use.

   When this parameter is GET_ALIAS_PORT, it indicates to get a randomly
   selected port number.
*/

	if (alias_port_param == GET_ALIAS_PORT) {
		/*
		 * The aliasing port is automatically selected by one of
		 * two methods below:
		 */
		max_trials = GET_NEW_PORT_MAX_ATTEMPTS;

		if (la->packetAliasMode & PKT_ALIAS_SAME_PORTS) {
			/*
			 * When the PKT_ALIAS_SAME_PORTS option is chosen,
			 * the first try will be the actual source port. If
			 * this is already in use, the remainder of the
			 * trials will be random.
			 */
			port_net = lnk->src_port;
			port_sys = ntohs(port_net);
		} else {
			/* First trial and all subsequent are random. */
			port_sys = arc4random() & ALIAS_PORT_MASK;
			port_sys += ALIAS_PORT_BASE;
			port_net = htons(port_sys);
		}
	} else if (alias_port_param >= 0 && alias_port_param < 0x10000) {
		lnk->alias_port = (u_short) alias_port_param;
		return (0);
	} else {
#ifdef LIBALIAS_DEBUG
		fprintf(stderr, "PacketAlias/GetNewPort(): ");
		fprintf(stderr, "input parameter error\n");
#endif
		return (-1);
	}


/* Port number search */
	for (i = 0; i < max_trials; i++) {
		int go_ahead;
		struct alias_link *search_result;

		search_result = FindLinkIn(la, lnk->dst_addr, lnk->alias_addr,
		    lnk->dst_port, port_net,
		    lnk->link_type, 0);

		if (search_result == NULL)
			go_ahead = 1;
		else if (!(lnk->flags & LINK_PARTIALLY_SPECIFIED)
		    && (search_result->flags & LINK_PARTIALLY_SPECIFIED))
			go_ahead = 1;
		else
			go_ahead = 0;

		if (go_ahead) {
#ifndef	NO_USE_SOCKETS
			if ((la->packetAliasMode & PKT_ALIAS_USE_SOCKETS)
			    && (lnk->flags & LINK_PARTIALLY_SPECIFIED)
			    && ((lnk->link_type == LINK_TCP) ||
			    (lnk->link_type == LINK_UDP))) {
				if (GetSocket(la, port_net, &lnk->sockfd, lnk->link_type)) {
					lnk->alias_port = port_net;
					return (0);
				}
			} else {
#endif
				lnk->alias_port = port_net;
				return (0);
#ifndef	NO_USE_SOCKETS
			}
#endif
		}
		port_sys = arc4random() & ALIAS_PORT_MASK;
		port_sys += ALIAS_PORT_BASE;
		port_net = htons(port_sys);
	}

#ifdef LIBALIAS_DEBUG
	fprintf(stderr, "PacketAlias/GetnewPort(): ");
	fprintf(stderr, "could not find free port\n");
#endif

	return (-1);
}