#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct in6_addr {int dummy; } ;
struct dhcp6_relay {int /*<<< orphan*/  dh6relay_peeraddr; int /*<<< orphan*/  dh6relay_linkaddr; } ;
struct dhcp6 {scalar_t__ dh6_msgtype; int /*<<< orphan*/  dh6_xid; } ;
struct TYPE_6__ {int /*<<< orphan*/  ndo_vflag; scalar_t__ ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/  addr6 ;

/* Variables and functions */
 scalar_t__ DH6_RELAY_FORW ; 
 scalar_t__ DH6_RELAY_REPLY ; 
 int DH6_XIDMASK ; 
 int EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dh6_msgtype_str ; 
 int /*<<< orphan*/  dhcp6opt_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ip6addr_string (TYPE_1__*,struct in6_addr*) ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,int /*<<< orphan*/ ,int) ; 
 char* tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
dhcp6_print(netdissect_options *ndo,
            const u_char *cp, u_int length)
{
	const struct dhcp6 *dh6;
	const struct dhcp6_relay *dh6relay;
	const u_char *ep;
	const u_char *extp;
	const char *name;

	ND_PRINT((ndo, "dhcp6"));

	ep = (const u_char *)ndo->ndo_snapend;
	if (cp + length < ep)
		ep = cp + length;

	dh6 = (const struct dhcp6 *)cp;
	dh6relay = (const struct dhcp6_relay *)cp;
	ND_TCHECK(dh6->dh6_xid);
	name = tok2str(dh6_msgtype_str, "msgtype-%u", dh6->dh6_msgtype);

	if (!ndo->ndo_vflag) {
		ND_PRINT((ndo, " %s", name));
		return;
	}

	/* XXX relay agent messages have to be handled differently */

	ND_PRINT((ndo, " %s (", name));	/*)*/
	if (dh6->dh6_msgtype != DH6_RELAY_FORW &&
	    dh6->dh6_msgtype != DH6_RELAY_REPLY) {
		ND_PRINT((ndo, "xid=%x", EXTRACT_32BITS(&dh6->dh6_xid) & DH6_XIDMASK));
		extp = (const u_char *)(dh6 + 1);
		dhcp6opt_print(ndo, extp, ep);
	} else {		/* relay messages */
		struct in6_addr addr6;

		ND_TCHECK(dh6relay->dh6relay_peeraddr);

		memcpy(&addr6, dh6relay->dh6relay_linkaddr, sizeof (addr6));
		ND_PRINT((ndo, "linkaddr=%s", ip6addr_string(ndo, &addr6)));

		memcpy(&addr6, dh6relay->dh6relay_peeraddr, sizeof (addr6));
		ND_PRINT((ndo, " peeraddr=%s", ip6addr_string(ndo, &addr6)));

		dhcp6opt_print(ndo, (const u_char *)(dh6relay + 1), ep);
	}
	/*(*/
	ND_PRINT((ndo, ")"));
	return;

trunc:
	ND_PRINT((ndo, "[|dhcp6]"));
}