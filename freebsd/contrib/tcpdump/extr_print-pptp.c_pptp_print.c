#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct pptp_hdr {int /*<<< orphan*/  reserved0; int /*<<< orphan*/  ctrl_msg_type; int /*<<< orphan*/  magic_cookie; int /*<<< orphan*/  msg_type; int /*<<< orphan*/  length; } ;
struct TYPE_19__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
#define  PPTP_CTRL_MSG_TYPE_CCRQ 144 
#define  PPTP_CTRL_MSG_TYPE_CDN 143 
#define  PPTP_CTRL_MSG_TYPE_ECHORP 142 
#define  PPTP_CTRL_MSG_TYPE_ECHORQ 141 
#define  PPTP_CTRL_MSG_TYPE_ICCN 140 
#define  PPTP_CTRL_MSG_TYPE_ICRP 139 
#define  PPTP_CTRL_MSG_TYPE_ICRQ 138 
#define  PPTP_CTRL_MSG_TYPE_OCRP 137 
#define  PPTP_CTRL_MSG_TYPE_OCRQ 136 
#define  PPTP_CTRL_MSG_TYPE_SCCRP 135 
#define  PPTP_CTRL_MSG_TYPE_SCCRQ 134 
#define  PPTP_CTRL_MSG_TYPE_SLI 133 
#define  PPTP_CTRL_MSG_TYPE_StopCCRP 132 
#define  PPTP_CTRL_MSG_TYPE_StopCCRQ 131 
#define  PPTP_CTRL_MSG_TYPE_WEN 130 
 scalar_t__ PPTP_MAGIC_COOKIE ; 
 size_t PPTP_MAX_MSGTYPE_INDEX ; 
#define  PPTP_MSG_TYPE_CTRL 129 
#define  PPTP_MSG_TYPE_MGMT 128 
 int /*<<< orphan*/  pptp_ccrq_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_cdn_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_echorp_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_echorq_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_iccn_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_icrp_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_icrq_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * pptp_message_type_string ; 
 int /*<<< orphan*/  pptp_ocrp_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_ocrq_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_sccrp_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_sccrq_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_sli_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_stopccrp_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_stopccrq_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pptp_wen_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tstr ; 

void
pptp_print(netdissect_options *ndo,
           const u_char *dat)
{
	const struct pptp_hdr *hdr;
	uint32_t mc;
	uint16_t ctrl_msg_type;

	ND_PRINT((ndo, ": pptp"));

	hdr = (const struct pptp_hdr *)dat;

	ND_TCHECK(hdr->length);
	if (ndo->ndo_vflag) {
		ND_PRINT((ndo, " Length=%u", EXTRACT_16BITS(&hdr->length)));
	}
	ND_TCHECK(hdr->msg_type);
	if (ndo->ndo_vflag) {
		switch(EXTRACT_16BITS(&hdr->msg_type)) {
		case PPTP_MSG_TYPE_CTRL:
			ND_PRINT((ndo, " CTRL-MSG"));
			break;
		case PPTP_MSG_TYPE_MGMT:
			ND_PRINT((ndo, " MGMT-MSG"));
			break;
		default:
			ND_PRINT((ndo, " UNKNOWN-MSG-TYPE"));
			break;
		}
	}

	ND_TCHECK(hdr->magic_cookie);
	mc = EXTRACT_32BITS(&hdr->magic_cookie);
	if (mc != PPTP_MAGIC_COOKIE) {
		ND_PRINT((ndo, " UNEXPECTED Magic-Cookie!!(%08x)", mc));
	}
	if (ndo->ndo_vflag || mc != PPTP_MAGIC_COOKIE) {
		ND_PRINT((ndo, " Magic-Cookie=%08x", mc));
	}
	ND_TCHECK(hdr->ctrl_msg_type);
	ctrl_msg_type = EXTRACT_16BITS(&hdr->ctrl_msg_type);
	if (ctrl_msg_type < PPTP_MAX_MSGTYPE_INDEX) {
		ND_PRINT((ndo, " CTRL_MSGTYPE=%s",
		       pptp_message_type_string[ctrl_msg_type]));
	} else {
		ND_PRINT((ndo, " UNKNOWN_CTRL_MSGTYPE(%u)", ctrl_msg_type));
	}
	ND_TCHECK(hdr->reserved0);

	dat += 12;

	switch(ctrl_msg_type) {
	case PPTP_CTRL_MSG_TYPE_SCCRQ:
		pptp_sccrq_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_SCCRP:
		pptp_sccrp_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_StopCCRQ:
		pptp_stopccrq_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_StopCCRP:
		pptp_stopccrp_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_ECHORQ:
		pptp_echorq_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_ECHORP:
		pptp_echorp_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_OCRQ:
		pptp_ocrq_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_OCRP:
		pptp_ocrp_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_ICRQ:
		pptp_icrq_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_ICRP:
		pptp_icrp_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_ICCN:
		pptp_iccn_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_CCRQ:
		pptp_ccrq_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_CDN:
		pptp_cdn_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_WEN:
		pptp_wen_print(ndo, dat);
		break;
	case PPTP_CTRL_MSG_TYPE_SLI:
		pptp_sli_print(ndo, dat);
		break;
	default:
		/* do nothing */
		break;
	}

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}