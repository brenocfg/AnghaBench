#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct ctrl_rts_hdr_t {int /*<<< orphan*/  ta; } ;
struct ctrl_ps_poll_hdr_t {int /*<<< orphan*/  aid; } ;
struct ctrl_end_hdr_t {int /*<<< orphan*/  ra; } ;
struct ctrl_end_ack_hdr_t {int /*<<< orphan*/  ra; } ;
struct ctrl_cts_hdr_t {int /*<<< orphan*/  ra; } ;
struct ctrl_bar_hdr_t {int /*<<< orphan*/  seq; int /*<<< orphan*/  ctl; int /*<<< orphan*/  ta; int /*<<< orphan*/  ra; } ;
struct ctrl_ba_hdr_t {int /*<<< orphan*/  ra; } ;
struct ctrl_ack_hdr_t {int /*<<< orphan*/  ra; } ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  CTRL_ACK 136 
 int /*<<< orphan*/  CTRL_ACK_HDRLEN ; 
#define  CTRL_BA 135 
#define  CTRL_BAR 134 
 int /*<<< orphan*/  CTRL_BAR_HDRLEN ; 
 int /*<<< orphan*/  CTRL_BA_HDRLEN ; 
#define  CTRL_CF_END 133 
#define  CTRL_CONTROL_WRAPPER 132 
#define  CTRL_CTS 131 
 int /*<<< orphan*/  CTRL_CTS_HDRLEN ; 
#define  CTRL_END_ACK 130 
 int /*<<< orphan*/  CTRL_END_ACK_HDRLEN ; 
 int /*<<< orphan*/  CTRL_END_HDRLEN ; 
#define  CTRL_PS_POLL 129 
 int /*<<< orphan*/  CTRL_PS_POLL_HDRLEN ; 
#define  CTRL_RTS 128 
 int /*<<< orphan*/  CTRL_RTS_HDRLEN ; 
 int /*<<< orphan*/  EXTRACT_LE_16BITS (int /*<<< orphan*/ *) ; 
 int FC_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_str ; 
 int /*<<< orphan*/  etheraddr_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
ctrl_body_print(netdissect_options *ndo,
                uint16_t fc, const u_char *p)
{
	ND_PRINT((ndo, "%s", tok2str(ctrl_str, "Unknown Ctrl Subtype", FC_SUBTYPE(fc))));
	switch (FC_SUBTYPE(fc)) {
	case CTRL_CONTROL_WRAPPER:
		/* XXX - requires special handling */
		break;
	case CTRL_BAR:
		if (!ND_TTEST2(*p, CTRL_BAR_HDRLEN))
			return 0;
		if (!ndo->ndo_eflag)
			ND_PRINT((ndo, " RA:%s TA:%s CTL(%x) SEQ(%u) ",
			    etheraddr_string(ndo, ((const struct ctrl_bar_hdr_t *)p)->ra),
			    etheraddr_string(ndo, ((const struct ctrl_bar_hdr_t *)p)->ta),
			    EXTRACT_LE_16BITS(&(((const struct ctrl_bar_hdr_t *)p)->ctl)),
			    EXTRACT_LE_16BITS(&(((const struct ctrl_bar_hdr_t *)p)->seq))));
		break;
	case CTRL_BA:
		if (!ND_TTEST2(*p, CTRL_BA_HDRLEN))
			return 0;
		if (!ndo->ndo_eflag)
			ND_PRINT((ndo, " RA:%s ",
			    etheraddr_string(ndo, ((const struct ctrl_ba_hdr_t *)p)->ra)));
		break;
	case CTRL_PS_POLL:
		if (!ND_TTEST2(*p, CTRL_PS_POLL_HDRLEN))
			return 0;
		ND_PRINT((ndo, " AID(%x)",
		    EXTRACT_LE_16BITS(&(((const struct ctrl_ps_poll_hdr_t *)p)->aid))));
		break;
	case CTRL_RTS:
		if (!ND_TTEST2(*p, CTRL_RTS_HDRLEN))
			return 0;
		if (!ndo->ndo_eflag)
			ND_PRINT((ndo, " TA:%s ",
			    etheraddr_string(ndo, ((const struct ctrl_rts_hdr_t *)p)->ta)));
		break;
	case CTRL_CTS:
		if (!ND_TTEST2(*p, CTRL_CTS_HDRLEN))
			return 0;
		if (!ndo->ndo_eflag)
			ND_PRINT((ndo, " RA:%s ",
			    etheraddr_string(ndo, ((const struct ctrl_cts_hdr_t *)p)->ra)));
		break;
	case CTRL_ACK:
		if (!ND_TTEST2(*p, CTRL_ACK_HDRLEN))
			return 0;
		if (!ndo->ndo_eflag)
			ND_PRINT((ndo, " RA:%s ",
			    etheraddr_string(ndo, ((const struct ctrl_ack_hdr_t *)p)->ra)));
		break;
	case CTRL_CF_END:
		if (!ND_TTEST2(*p, CTRL_END_HDRLEN))
			return 0;
		if (!ndo->ndo_eflag)
			ND_PRINT((ndo, " RA:%s ",
			    etheraddr_string(ndo, ((const struct ctrl_end_hdr_t *)p)->ra)));
		break;
	case CTRL_END_ACK:
		if (!ND_TTEST2(*p, CTRL_END_ACK_HDRLEN))
			return 0;
		if (!ndo->ndo_eflag)
			ND_PRINT((ndo, " RA:%s ",
			    etheraddr_string(ndo, ((const struct ctrl_end_ack_hdr_t *)p)->ra)));
		break;
	}
	return 1;
}