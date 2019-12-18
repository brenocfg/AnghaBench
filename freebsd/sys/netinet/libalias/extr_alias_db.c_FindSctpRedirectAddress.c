#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sctp_nat_msg {TYPE_4__* ip_hdr; TYPE_1__* sctp_hdr; } ;
struct TYPE_7__ {scalar_t__ s_addr; } ;
struct TYPE_6__ {scalar_t__ s_addr; } ;
struct libalias {TYPE_3__ targetAddress; TYPE_2__ aliasAddress; } ;
struct in_addr {scalar_t__ s_addr; } ;
struct alias_link {struct in_addr src_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
struct TYPE_5__ {int /*<<< orphan*/  dest_port; } ;

/* Variables and functions */
 struct alias_link* FindLinkIn (struct libalias*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct in_addr FindOriginalAddress (struct libalias*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  LINK_SCTP ; 
 int /*<<< orphan*/  NO_DEST_PORT ; 

struct in_addr
FindSctpRedirectAddress(struct libalias *la,  struct sctp_nat_msg *sm)
{
	struct alias_link *lnk;
	struct in_addr redir;

	LIBALIAS_LOCK_ASSERT(la);
	lnk = FindLinkIn(la, sm->ip_hdr->ip_src, sm->ip_hdr->ip_dst,
	    sm->sctp_hdr->dest_port,sm->sctp_hdr->dest_port, LINK_SCTP, 1);
	if (lnk != NULL) {
		return(lnk->src_addr); /* port redirect */
	} else {
		redir = FindOriginalAddress(la,sm->ip_hdr->ip_dst);
		if (redir.s_addr == la->aliasAddress.s_addr ||
		    redir.s_addr == la->targetAddress.s_addr) { /* No address found */
			lnk = FindLinkIn(la, sm->ip_hdr->ip_src, sm->ip_hdr->ip_dst,
			    NO_DEST_PORT, 0, LINK_SCTP, 1);
			if (lnk != NULL)
				return(lnk->src_addr); /* redirect proto */
		}
		return(redir); /* address redirect */
	}
}