#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {int /*<<< orphan*/  cb_vers; int /*<<< orphan*/  cb_prog; int /*<<< orphan*/  cb_proc; int /*<<< orphan*/  cb_rpcvers; } ;
struct sunrpc_msg {TYPE_1__ rm_call; int /*<<< orphan*/  rm_xid; } ;
struct ip6_hdr {int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; } ;
struct ip {int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
typedef  int /*<<< orphan*/  srcid ;
struct TYPE_8__ {int /*<<< orphan*/  ndo_nflag; } ;
typedef  TYPE_2__ netdissect_options ;
typedef  int /*<<< orphan*/  dstid ;

/* Variables and functions */
 int EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int IP_V (struct ip const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_2__*) ; 
 int SUNRPC_PMAPPORT ; 
#define  SUNRPC_PMAPPROC_CALLIT 131 
#define  SUNRPC_PMAPPROC_GETPORT 130 
#define  SUNRPC_PMAPPROC_SET 129 
#define  SUNRPC_PMAPPROC_UNSET 128 
 int /*<<< orphan*/  ip6addr_string (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipaddr_string (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc2str ; 
 int /*<<< orphan*/  progstr (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

void
sunrpcrequest_print(netdissect_options *ndo, register const u_char *bp,
                    register u_int length, register const u_char *bp2)
{
	register const struct sunrpc_msg *rp;
	register const struct ip *ip;
	register const struct ip6_hdr *ip6;
	uint32_t x;
	char srcid[20], dstid[20];	/*fits 32bit*/

	rp = (const struct sunrpc_msg *)bp;

	if (!ndo->ndo_nflag) {
		snprintf(srcid, sizeof(srcid), "0x%x",
		    EXTRACT_32BITS(&rp->rm_xid));
		strlcpy(dstid, "sunrpc", sizeof(dstid));
	} else {
		snprintf(srcid, sizeof(srcid), "0x%x",
		    EXTRACT_32BITS(&rp->rm_xid));
		snprintf(dstid, sizeof(dstid), "0x%x", SUNRPC_PMAPPORT);
	}

	switch (IP_V((const struct ip *)bp2)) {
	case 4:
		ip = (const struct ip *)bp2;
		ND_PRINT((ndo, "%s.%s > %s.%s: %d",
		    ipaddr_string(ndo, &ip->ip_src), srcid,
		    ipaddr_string(ndo, &ip->ip_dst), dstid, length));
		break;
	case 6:
		ip6 = (const struct ip6_hdr *)bp2;
		ND_PRINT((ndo, "%s.%s > %s.%s: %d",
		    ip6addr_string(ndo, &ip6->ip6_src), srcid,
		    ip6addr_string(ndo, &ip6->ip6_dst), dstid, length));
		break;
	default:
		ND_PRINT((ndo, "%s.%s > %s.%s: %d", "?", srcid, "?", dstid, length));
		break;
	}

	ND_PRINT((ndo, " %s", tok2str(proc2str, " proc #%u",
	    EXTRACT_32BITS(&rp->rm_call.cb_proc))));
	x = EXTRACT_32BITS(&rp->rm_call.cb_rpcvers);
	if (x != 2)
		ND_PRINT((ndo, " [rpcver %u]", x));

	switch (EXTRACT_32BITS(&rp->rm_call.cb_proc)) {

	case SUNRPC_PMAPPROC_SET:
	case SUNRPC_PMAPPROC_UNSET:
	case SUNRPC_PMAPPROC_GETPORT:
	case SUNRPC_PMAPPROC_CALLIT:
		x = EXTRACT_32BITS(&rp->rm_call.cb_prog);
		if (!ndo->ndo_nflag)
			ND_PRINT((ndo, " %s", progstr(x)));
		else
			ND_PRINT((ndo, " %u", x));
		ND_PRINT((ndo, ".%u", EXTRACT_32BITS(&rp->rm_call.cb_vers)));
		break;
	}
}