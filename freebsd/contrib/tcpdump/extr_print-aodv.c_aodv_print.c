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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
#define  AODV_RERR 135 
#define  AODV_RREP 134 
#define  AODV_RREP_ACK 133 
#define  AODV_RREQ 132 
#define  AODV_V6_DRAFT_01_RERR 131 
#define  AODV_V6_DRAFT_01_RREP 130 
#define  AODV_V6_DRAFT_01_RREP_ACK 129 
#define  AODV_V6_DRAFT_01_RREQ 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  aodv_rerr (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aodv_rrep (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aodv_rreq (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aodv_v6_draft_01_rerr (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aodv_v6_draft_01_rrep (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aodv_v6_draft_01_rreq (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aodv_v6_rerr (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aodv_v6_rrep (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aodv_v6_rreq (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 

void
aodv_print(netdissect_options *ndo,
           const u_char *dat, u_int length, int is_ip6)
{
	uint8_t msg_type;

	/*
	 * The message type is the first byte; make sure we have it
	 * and then fetch it.
	 */
	ND_TCHECK(*dat);
	msg_type = *dat;
	ND_PRINT((ndo, " aodv"));

	switch (msg_type) {

	case AODV_RREQ:
		if (is_ip6)
			aodv_v6_rreq(ndo, dat, length);
		else
			aodv_rreq(ndo, dat, length);
		break;

	case AODV_RREP:
		if (is_ip6)
			aodv_v6_rrep(ndo, dat, length);
		else
			aodv_rrep(ndo, dat, length);
		break;

	case AODV_RERR:
		if (is_ip6)
			aodv_v6_rerr(ndo, dat, length);
		else
			aodv_rerr(ndo, dat, length);
		break;

	case AODV_RREP_ACK:
		ND_PRINT((ndo, " rrep-ack %u", length));
		break;

	case AODV_V6_DRAFT_01_RREQ:
		aodv_v6_draft_01_rreq(ndo, dat, length);
		break;

	case AODV_V6_DRAFT_01_RREP:
		aodv_v6_draft_01_rrep(ndo, dat, length);
		break;

	case AODV_V6_DRAFT_01_RERR:
		aodv_v6_draft_01_rerr(ndo, dat, length);
		break;

	case AODV_V6_DRAFT_01_RREP_ACK:
		ND_PRINT((ndo, " rrep-ack %u", length));
		break;

	default:
		ND_PRINT((ndo, " type %u %u", msg_type, length));
	}
	return;

trunc:
	ND_PRINT((ndo, " [|aodv]"));
}