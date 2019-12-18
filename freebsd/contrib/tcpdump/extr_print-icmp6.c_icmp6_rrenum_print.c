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
typedef  int /*<<< orphan*/  u_char ;
struct rr_pco_use {int /*<<< orphan*/  rpu_keeplen; int /*<<< orphan*/  rpu_uselen; scalar_t__ rpu_prefix; scalar_t__ rpu_pltime; scalar_t__ rpu_vltime; int /*<<< orphan*/  rpu_raflags; int /*<<< orphan*/  rpu_ramask; scalar_t__ rpu_flags; } ;
struct rr_pco_match {int rpm_code; int rpm_len; int /*<<< orphan*/  rpm_matchlen; scalar_t__ rpm_prefix; int /*<<< orphan*/  rpm_maxlen; int /*<<< orphan*/  rpm_minlen; int /*<<< orphan*/  rpm_ordinal; } ;
struct icmp6_router_renum {int rr_code; scalar_t__ rr_reserved; int /*<<< orphan*/  rr_maxdelay; int /*<<< orphan*/  rr_segnum; scalar_t__ rr_flags; scalar_t__ rr_seqnum; } ;
struct TYPE_4__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/  hbuf ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (scalar_t__*) ; 
 int /*<<< orphan*/  F (int /*<<< orphan*/ ,char*) ; 
#define  ICMP6_ROUTER_RENUMBERING_COMMAND 133 
#define  ICMP6_ROUTER_RENUMBERING_RESULT 132 
#define  ICMP6_ROUTER_RENUMBERING_SEQNUM_RESET 131 
 int /*<<< orphan*/  ICMP6_RR_FLAGS_FORCEAPPLY ; 
 int /*<<< orphan*/  ICMP6_RR_FLAGS_PREVDONE ; 
 int /*<<< orphan*/  ICMP6_RR_FLAGS_REQRESULT ; 
 int /*<<< orphan*/  ICMP6_RR_FLAGS_SPECSITE ; 
 int /*<<< orphan*/  ICMP6_RR_FLAGS_TEST ; 
 int /*<<< orphan*/  ICMP6_RR_PCOUSE_FLAGS_DECRPLTIME ; 
 int /*<<< orphan*/  ICMP6_RR_PCOUSE_FLAGS_DECRVLTIME ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (scalar_t__) ; 
 int NI_MAXHOST ; 
#define  RPM_PCO_ADD 130 
#define  RPM_PCO_CHANGE 129 
#define  RPM_PCO_SETGLOBAL 128 
 scalar_t__ addrtostr6 (scalar_t__*,char*,int) ; 

__attribute__((used)) static void
icmp6_rrenum_print(netdissect_options *ndo, const u_char *bp, const u_char *ep)
{
	const struct icmp6_router_renum *rr6;
	const char *cp;
	const struct rr_pco_match *match;
	const struct rr_pco_use *use;
	char hbuf[NI_MAXHOST];
	int n;

	if (ep < bp)
		return;
	rr6 = (const struct icmp6_router_renum *)bp;
	cp = (const char *)(rr6 + 1);

	ND_TCHECK(rr6->rr_reserved);
	switch (rr6->rr_code) {
	case ICMP6_ROUTER_RENUMBERING_COMMAND:
		ND_PRINT((ndo,"router renum: command"));
		break;
	case ICMP6_ROUTER_RENUMBERING_RESULT:
		ND_PRINT((ndo,"router renum: result"));
		break;
	case ICMP6_ROUTER_RENUMBERING_SEQNUM_RESET:
		ND_PRINT((ndo,"router renum: sequence number reset"));
		break;
	default:
		ND_PRINT((ndo,"router renum: code-#%d", rr6->rr_code));
		break;
	}

        ND_PRINT((ndo,", seq=%u", EXTRACT_32BITS(&rr6->rr_seqnum)));

	if (ndo->ndo_vflag) {
#define F(x, y)	((rr6->rr_flags) & (x) ? (y) : "")
		ND_PRINT((ndo,"["));	/*]*/
		if (rr6->rr_flags) {
			ND_PRINT((ndo,"%s%s%s%s%s,", F(ICMP6_RR_FLAGS_TEST, "T"),
                                  F(ICMP6_RR_FLAGS_REQRESULT, "R"),
                                  F(ICMP6_RR_FLAGS_FORCEAPPLY, "A"),
                                  F(ICMP6_RR_FLAGS_SPECSITE, "S"),
                                  F(ICMP6_RR_FLAGS_PREVDONE, "P")));
		}
                ND_PRINT((ndo,"seg=%u,", rr6->rr_segnum));
                ND_PRINT((ndo,"maxdelay=%u", EXTRACT_16BITS(&rr6->rr_maxdelay)));
		if (rr6->rr_reserved)
			ND_PRINT((ndo,"rsvd=0x%x", EXTRACT_32BITS(&rr6->rr_reserved)));
		/*[*/
		ND_PRINT((ndo,"]"));
#undef F
	}

	if (rr6->rr_code == ICMP6_ROUTER_RENUMBERING_COMMAND) {
		match = (const struct rr_pco_match *)cp;
		cp = (const char *)(match + 1);

		ND_TCHECK(match->rpm_prefix);

		if (ndo->ndo_vflag > 1)
			ND_PRINT((ndo,"\n\t"));
		else
			ND_PRINT((ndo," "));
		ND_PRINT((ndo,"match("));	/*)*/
		switch (match->rpm_code) {
		case RPM_PCO_ADD:	ND_PRINT((ndo,"add")); break;
		case RPM_PCO_CHANGE:	ND_PRINT((ndo,"change")); break;
		case RPM_PCO_SETGLOBAL:	ND_PRINT((ndo,"setglobal")); break;
		default:		ND_PRINT((ndo,"#%u", match->rpm_code)); break;
		}

		if (ndo->ndo_vflag) {
			ND_PRINT((ndo,",ord=%u", match->rpm_ordinal));
			ND_PRINT((ndo,",min=%u", match->rpm_minlen));
			ND_PRINT((ndo,",max=%u", match->rpm_maxlen));
		}
		if (addrtostr6(&match->rpm_prefix, hbuf, sizeof(hbuf)))
			ND_PRINT((ndo,",%s/%u", hbuf, match->rpm_matchlen));
		else
			ND_PRINT((ndo,",?/%u", match->rpm_matchlen));
		/*(*/
		ND_PRINT((ndo,")"));

		n = match->rpm_len - 3;
		if (n % 4)
			goto trunc;
		n /= 4;
		while (n-- > 0) {
			use = (const struct rr_pco_use *)cp;
			cp = (const char *)(use + 1);

			ND_TCHECK(use->rpu_prefix);

			if (ndo->ndo_vflag > 1)
				ND_PRINT((ndo,"\n\t"));
			else
				ND_PRINT((ndo," "));
			ND_PRINT((ndo,"use("));	/*)*/
			if (use->rpu_flags) {
#define F(x, y)	((use->rpu_flags) & (x) ? (y) : "")
				ND_PRINT((ndo,"%s%s,",
                                          F(ICMP6_RR_PCOUSE_FLAGS_DECRVLTIME, "V"),
                                          F(ICMP6_RR_PCOUSE_FLAGS_DECRPLTIME, "P")));
#undef F
			}
			if (ndo->ndo_vflag) {
				ND_PRINT((ndo,"mask=0x%x,", use->rpu_ramask));
				ND_PRINT((ndo,"raflags=0x%x,", use->rpu_raflags));
				if (~use->rpu_vltime == 0)
					ND_PRINT((ndo,"vltime=infty,"));
				else
					ND_PRINT((ndo,"vltime=%u,",
                                                  EXTRACT_32BITS(&use->rpu_vltime)));
				if (~use->rpu_pltime == 0)
					ND_PRINT((ndo,"pltime=infty,"));
				else
					ND_PRINT((ndo,"pltime=%u,",
                                                  EXTRACT_32BITS(&use->rpu_pltime)));
			}
			if (addrtostr6(&use->rpu_prefix, hbuf, sizeof(hbuf)))
				ND_PRINT((ndo,"%s/%u/%u", hbuf, use->rpu_uselen,
                                          use->rpu_keeplen));
			else
				ND_PRINT((ndo,"?/%u/%u", use->rpu_uselen,
                                          use->rpu_keeplen));
			/*(*/
                        ND_PRINT((ndo,")"));
		}
	}

	return;

trunc:
	ND_PRINT((ndo,"[|icmp6]"));
}