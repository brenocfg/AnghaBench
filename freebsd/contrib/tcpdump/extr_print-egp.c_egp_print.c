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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct egp_packet {scalar_t__ egp_version; int egp_type; int egp_code; int egp_status; int /*<<< orphan*/  egp_reason; int /*<<< orphan*/  egp_extgw; int /*<<< orphan*/  egp_intgw; int /*<<< orphan*/  egp_sourcenet; int /*<<< orphan*/  egp_poll; int /*<<< orphan*/  egp_hello; int /*<<< orphan*/  egp_sequence; int /*<<< orphan*/  egp_as; } ;
struct TYPE_6__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  EGPC_CEASE 147 
#define  EGPC_CEASEACK 146 
#define  EGPC_CONFIRM 145 
#define  EGPC_HEARDU 144 
#define  EGPC_HELLO 143 
#define  EGPC_REFUSE 142 
#define  EGPC_REQUEST 141 
 size_t EGPR_UVERSION ; 
#define  EGPS_ACTIVE 140 
#define  EGPS_ADMIN 139 
 int EGPS_DOWN ; 
#define  EGPS_GODOWN 138 
#define  EGPS_NORES 137 
#define  EGPS_PARAM 136 
#define  EGPS_PASSIVE 135 
#define  EGPS_PROTO 134 
 int EGPS_UNSOL ; 
#define  EGPS_UNSPEC 133 
#define  EGPT_ACQUIRE 132 
#define  EGPT_ERROR 131 
#define  EGPT_POLL 130 
#define  EGPT_REACH 129 
#define  EGPT_UPDATE 128 
 scalar_t__ EGP_VERSION ; 
 size_t EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TTEST (struct egp_packet const) ; 
 int /*<<< orphan*/ * egp_acquire_codes ; 
 int /*<<< orphan*/ * egp_acquire_status ; 
 int /*<<< orphan*/ * egp_reach_codes ; 
 int /*<<< orphan*/ * egp_reasons ; 
 int /*<<< orphan*/ * egp_status_updown ; 
 int /*<<< orphan*/  egpnrprint (TYPE_1__*,struct egp_packet const*,int) ; 
 int /*<<< orphan*/  ipaddr_string (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
egp_print(netdissect_options *ndo,
          register const uint8_t *bp, register u_int length)
{
	register const struct egp_packet *egp;
	register int status;
	register int code;
	register int type;

	egp = (const struct egp_packet *)bp;
	if (length < sizeof(*egp) || !ND_TTEST(*egp)) {
		ND_PRINT((ndo, "[|egp]"));
		return;
	}

        if (!ndo->ndo_vflag) {
            ND_PRINT((ndo, "EGPv%u, AS %u, seq %u, length %u",
                   egp->egp_version,
                   EXTRACT_16BITS(&egp->egp_as),
                   EXTRACT_16BITS(&egp->egp_sequence),
                   length));
            return;
        } else
            ND_PRINT((ndo, "EGPv%u, length %u",
                   egp->egp_version,
                   length));

	if (egp->egp_version != EGP_VERSION) {
		ND_PRINT((ndo, "[version %d]", egp->egp_version));
		return;
	}

	type = egp->egp_type;
	code = egp->egp_code;
	status = egp->egp_status;

	switch (type) {
	case EGPT_ACQUIRE:
		ND_PRINT((ndo, " acquire"));
		switch (code) {
		case EGPC_REQUEST:
		case EGPC_CONFIRM:
			ND_PRINT((ndo, " %s", egp_acquire_codes[code]));
			switch (status) {
			case EGPS_UNSPEC:
			case EGPS_ACTIVE:
			case EGPS_PASSIVE:
				ND_PRINT((ndo, " %s", egp_acquire_status[status]));
				break;

			default:
				ND_PRINT((ndo, " [status %d]", status));
				break;
			}
			ND_PRINT((ndo, " hello:%d poll:%d",
			       EXTRACT_16BITS(&egp->egp_hello),
			       EXTRACT_16BITS(&egp->egp_poll)));
			break;

		case EGPC_REFUSE:
		case EGPC_CEASE:
		case EGPC_CEASEACK:
			ND_PRINT((ndo, " %s", egp_acquire_codes[code]));
			switch (status ) {
			case EGPS_UNSPEC:
			case EGPS_NORES:
			case EGPS_ADMIN:
			case EGPS_GODOWN:
			case EGPS_PARAM:
			case EGPS_PROTO:
				ND_PRINT((ndo, " %s", egp_acquire_status[status]));
				break;

			default:
				ND_PRINT((ndo, "[status %d]", status));
				break;
			}
			break;

		default:
			ND_PRINT((ndo, "[code %d]", code));
			break;
		}
		break;

	case EGPT_REACH:
		switch (code) {

		case EGPC_HELLO:
		case EGPC_HEARDU:
			ND_PRINT((ndo, " %s", egp_reach_codes[code]));
			if (status <= EGPS_DOWN)
				ND_PRINT((ndo, " state:%s", egp_status_updown[status]));
			else
				ND_PRINT((ndo, " [status %d]", status));
			break;

		default:
			ND_PRINT((ndo, "[reach code %d]", code));
			break;
		}
		break;

	case EGPT_POLL:
		ND_PRINT((ndo, " poll"));
		if (egp->egp_status <= EGPS_DOWN)
			ND_PRINT((ndo, " state:%s", egp_status_updown[status]));
		else
			ND_PRINT((ndo, " [status %d]", status));
		ND_PRINT((ndo, " net:%s", ipaddr_string(ndo, &egp->egp_sourcenet)));
		break;

	case EGPT_UPDATE:
		ND_PRINT((ndo, " update"));
		if (status & EGPS_UNSOL) {
			status &= ~EGPS_UNSOL;
			ND_PRINT((ndo, " unsolicited"));
		}
		if (status <= EGPS_DOWN)
			ND_PRINT((ndo, " state:%s", egp_status_updown[status]));
		else
			ND_PRINT((ndo, " [status %d]", status));
		ND_PRINT((ndo, " %s int %d ext %d",
		       ipaddr_string(ndo, &egp->egp_sourcenet),
		       egp->egp_intgw,
		       egp->egp_extgw));
		if (ndo->ndo_vflag)
			egpnrprint(ndo, egp, length);
		break;

	case EGPT_ERROR:
		ND_PRINT((ndo, " error"));
		if (status <= EGPS_DOWN)
			ND_PRINT((ndo, " state:%s", egp_status_updown[status]));
		else
			ND_PRINT((ndo, " [status %d]", status));

		if (EXTRACT_16BITS(&egp->egp_reason) <= EGPR_UVERSION)
			ND_PRINT((ndo, " %s", egp_reasons[EXTRACT_16BITS(&egp->egp_reason)]));
		else
			ND_PRINT((ndo, " [reason %d]", EXTRACT_16BITS(&egp->egp_reason)));
		break;

	default:
		ND_PRINT((ndo, "[type %d]", type));
		break;
	}
}