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
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_char ;
struct libalias {int dummy; } ;
struct in_addr {int dummy; } ;
struct alias_link {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct alias_link* AddLink (struct libalias*,struct in_addr,struct in_addr,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 
 int /*<<< orphan*/  LINK_PERMANENT ; 
 int LINK_SCTP ; 
 int LINK_TCP ; 
 int LINK_UDP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

struct alias_link *
LibAliasRedirectPort(struct libalias *la, struct in_addr src_addr, u_short src_port,
    struct in_addr dst_addr, u_short dst_port,
    struct in_addr alias_addr, u_short alias_port,
    u_char proto)
{
	int link_type;
	struct alias_link *lnk;

	LIBALIAS_LOCK(la);
	switch (proto) {
	case IPPROTO_UDP:
		link_type = LINK_UDP;
		break;
	case IPPROTO_TCP:
		link_type = LINK_TCP;
		break;
	case IPPROTO_SCTP:
		link_type = LINK_SCTP;
		break;
	default:
#ifdef LIBALIAS_DEBUG
		fprintf(stderr, "PacketAliasRedirectPort(): ");
		fprintf(stderr, "only SCTP, TCP and UDP protocols allowed\n");
#endif
		lnk = NULL;
		goto getout;
	}

	lnk = AddLink(la, src_addr, dst_addr, alias_addr,
	    src_port, dst_port, alias_port,
	    link_type);

	if (lnk != NULL) {
		lnk->flags |= LINK_PERMANENT;
	}
#ifdef LIBALIAS_DEBUG
	else {
		fprintf(stderr, "PacketAliasRedirectPort(): "
		    "call to AddLink() failed\n");
	}
#endif

getout:
	LIBALIAS_UNLOCK(la);
	return (lnk);
}