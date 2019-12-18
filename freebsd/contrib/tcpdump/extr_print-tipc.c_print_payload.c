#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int u_int ;
struct payload_tipc_pkthdr {int /*<<< orphan*/  w2; int /*<<< orphan*/  dest_node; int /*<<< orphan*/  orig_node; int /*<<< orphan*/  dest_port; int /*<<< orphan*/  orig_port; int /*<<< orphan*/  prev_node; int /*<<< orphan*/  w1; int /*<<< orphan*/  w0; } ;
struct TYPE_4__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 void* EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int TIPC_BROADCAST_ACK (void*) ; 
 int /*<<< orphan*/  TIPC_CLUSTER (int) ; 
 int TIPC_HSIZE (void*) ; 
 int TIPC_LINK_ACK (void*) ; 
 int TIPC_LINK_SEQ (void*) ; 
 int TIPC_MSIZE (void*) ; 
 int TIPC_MTYPE (void*) ; 
 int /*<<< orphan*/  TIPC_NODE (int) ; 
 int TIPC_USER (void*) ; 
 int /*<<< orphan*/  TIPC_VER (void*) ; 
 int /*<<< orphan*/  TIPC_ZONE (int) ; 
 int /*<<< orphan*/  tipcmtype_values ; 
 int /*<<< orphan*/  tipcuser_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
print_payload(netdissect_options *ndo, const struct payload_tipc_pkthdr *ap)
{
	uint32_t w0, w1, w2;
	u_int user;
	u_int hsize;
	u_int msize;
	u_int mtype;
	u_int broadcast_ack;
	u_int link_ack;
	u_int link_seq;
	u_int prev_node;
	u_int orig_port;
	u_int dest_port;
	u_int orig_node;
	u_int dest_node;

	ND_TCHECK(ap->dest_port);
	w0 = EXTRACT_32BITS(&ap->w0);
	user = TIPC_USER(w0);
	hsize = TIPC_HSIZE(w0);
	msize = TIPC_MSIZE(w0);
	w1 = EXTRACT_32BITS(&ap->w1);
	mtype = TIPC_MTYPE(w1);
	prev_node = EXTRACT_32BITS(&ap->prev_node);
	orig_port = EXTRACT_32BITS(&ap->orig_port);
	dest_port = EXTRACT_32BITS(&ap->dest_port);
	if (hsize <= 6) {
		ND_PRINT((ndo, "TIPC v%u.0 %u.%u.%u:%u > %u, headerlength %u bytes, MessageSize %u bytes, %s, messageType %s",
		    TIPC_VER(w0),
		    TIPC_ZONE(prev_node), TIPC_CLUSTER(prev_node), TIPC_NODE(prev_node),
		    orig_port, dest_port,
		    hsize*4, msize,
		    tok2str(tipcuser_values, "unknown", user),
		    tok2str(tipcmtype_values, "Unknown", mtype)));
	} else {
		ND_TCHECK(ap->dest_node);
		orig_node = EXTRACT_32BITS(&ap->orig_node);
		dest_node = EXTRACT_32BITS(&ap->dest_node);
		ND_PRINT((ndo, "TIPC v%u.0 %u.%u.%u:%u > %u.%u.%u:%u, headerlength %u bytes, MessageSize %u bytes, %s, messageType %s",
		    TIPC_VER(w0),
		    TIPC_ZONE(orig_node), TIPC_CLUSTER(orig_node), TIPC_NODE(orig_node),
		    orig_port,
		    TIPC_ZONE(dest_node), TIPC_CLUSTER(dest_node), TIPC_NODE(dest_node),
		    dest_port,
		    hsize*4, msize,
		    tok2str(tipcuser_values, "unknown", user),
		    tok2str(tipcmtype_values, "Unknown", mtype)));

		if (ndo->ndo_vflag) {
			broadcast_ack = TIPC_BROADCAST_ACK(w1);
			w2 = EXTRACT_32BITS(&ap->w2);
			link_ack = TIPC_LINK_ACK(w2);
			link_seq = TIPC_LINK_SEQ(w2);
			ND_PRINT((ndo, "\n\tPrevious Node %u.%u.%u, Broadcast Ack %u, Link Ack %u, Link Sequence %u",
			    TIPC_ZONE(prev_node), TIPC_CLUSTER(prev_node), TIPC_NODE(prev_node),
			    broadcast_ack, link_ack, link_seq));
		}
	}
	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}