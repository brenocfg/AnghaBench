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
typedef  int u_short ;
typedef  int u_char ;
struct libalias {int packetAliasMode; } ;
struct in_addr {int dummy; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIAS_PORT_BASE ; 
 int ALIAS_PORT_MASK ; 
 int ALIAS_PORT_MASK_EVEN ; 
 int FIND_EVEN_ALIAS_BASE ; 
 struct alias_link* FindLinkIn (struct libalias*,struct in_addr,struct in_addr,int,int,int,int /*<<< orphan*/ ) ; 
 int GET_NEW_PORT_MAX_ATTEMPTS ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int LINK_TCP ; 
 int LINK_UDP ; 
 int PKT_ALIAS_SAME_PORTS ; 
 int arc4random () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int htons (int) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  stderr ; 

int
FindNewPortGroup(struct libalias *la,
    struct in_addr dst_addr,
    struct in_addr alias_addr,
    u_short src_port,
    u_short dst_port,
    u_short port_count,
    u_char proto,
    u_char align)
{
	int i, j;
	int max_trials;
	u_short port_sys;
	int link_type;

	LIBALIAS_LOCK_ASSERT(la);
	/*
	 * Get link_type from protocol
	 */

	switch (proto) {
	case IPPROTO_UDP:
		link_type = LINK_UDP;
		break;
	case IPPROTO_TCP:
		link_type = LINK_TCP;
		break;
	default:
		return (0);
		break;
	}

	/*
	 * The aliasing port is automatically selected by one of two
	 * methods below:
	 */
	max_trials = GET_NEW_PORT_MAX_ATTEMPTS;

	if (la->packetAliasMode & PKT_ALIAS_SAME_PORTS) {
		/*
		 * When the ALIAS_SAME_PORTS option is chosen, the first
		 * try will be the actual source port. If this is already
		 * in use, the remainder of the trials will be random.
		 */
		port_sys = ntohs(src_port);

	} else {

		/* First trial and all subsequent are random. */
		if (align == FIND_EVEN_ALIAS_BASE)
			port_sys = arc4random() & ALIAS_PORT_MASK_EVEN;
		else
			port_sys = arc4random() & ALIAS_PORT_MASK;

		port_sys += ALIAS_PORT_BASE;
	}

/* Port number search */
	for (i = 0; i < max_trials; i++) {

		struct alias_link *search_result;

		for (j = 0; j < port_count; j++)
			if ((search_result = FindLinkIn(la, dst_addr,
			    alias_addr, dst_port, htons(port_sys + j),
			    link_type, 0)) != NULL)
				break;

		/* Found a good range, return base */
		if (j == port_count)
			return (htons(port_sys));

		/* Find a new base to try */
		if (align == FIND_EVEN_ALIAS_BASE)
			port_sys = arc4random() & ALIAS_PORT_MASK_EVEN;
		else
			port_sys = arc4random() & ALIAS_PORT_MASK;

		port_sys += ALIAS_PORT_BASE;
	}

#ifdef LIBALIAS_DEBUG
	fprintf(stderr, "PacketAlias/FindNewPortGroup(): ");
	fprintf(stderr, "could not find free port(s)\n");
#endif

	return (0);
}