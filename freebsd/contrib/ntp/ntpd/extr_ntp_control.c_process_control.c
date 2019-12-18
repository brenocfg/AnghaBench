#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32 ;
struct recvbuf {int recv_length; int /*<<< orphan*/  recv_srcadr; int /*<<< orphan*/  recv_pkt; int /*<<< orphan*/  dstadr; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct ntp_control {int r_m_e_op; scalar_t__ offset; TYPE_2__ u; int /*<<< orphan*/  count; int /*<<< orphan*/  associd; int /*<<< orphan*/  sequence; int /*<<< orphan*/  li_vn_mode; } ;
struct ctl_proc {int control_code; scalar_t__ flags; int /*<<< orphan*/  (* handler ) (struct recvbuf*,int) ;} ;
typedef  int /*<<< orphan*/  keyid_t ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {TYPE_1__ u; scalar_t__ status; int /*<<< orphan*/  associd; int /*<<< orphan*/  sequence; int /*<<< orphan*/  li_vn_mode; } ;

/* Variables and functions */
 scalar_t__ AUTH ; 
 int /*<<< orphan*/  CERR_BADFMT ; 
 int /*<<< orphan*/  CERR_BADOP ; 
 int /*<<< orphan*/  CERR_PERMISSION ; 
 int CTL_ERROR ; 
 int CTL_HEADER_LEN ; 
 size_t CTL_MAX_DATA_LEN ; 
 int CTL_MORE ; 
 int CTL_RESPONSE ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 void* FALSE ; 
 size_t MAX_MAC_LEN ; 
 size_t MIN_MAC_LEN ; 
 int /*<<< orphan*/  MODE_CONTROL ; 
 int NO_REQUEST ; 
 scalar_t__ NTP_OLDVERSION ; 
 scalar_t__ NTP_VERSION ; 
 int /*<<< orphan*/  PKT_LI_VN_MODE (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PKT_VERSION (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 scalar_t__ authdecrypt (scalar_t__,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  authistrustedip (scalar_t__,int /*<<< orphan*/ *) ; 
 struct ctl_proc* control_codes ; 
 scalar_t__ ctl_auth_keyid ; 
 int /*<<< orphan*/  ctl_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dataend ; 
 scalar_t__ datalinelen ; 
 void* datanotbinflag ; 
 int /*<<< orphan*/ * datapt ; 
 scalar_t__ datasent ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcl_inter ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numctlbadoffset ; 
 int /*<<< orphan*/  numctlbadop ; 
 int /*<<< orphan*/  numctlbadversion ; 
 int /*<<< orphan*/  numctldatatooshort ; 
 int /*<<< orphan*/  numctlinputerr ; 
 int /*<<< orphan*/  numctlinputfrag ; 
 int /*<<< orphan*/  numctlinputresp ; 
 int /*<<< orphan*/  numctlreq ; 
 int /*<<< orphan*/  numctltooshort ; 
 char* reqend ; 
 char* reqpt ; 
 int /*<<< orphan*/  res_associd ; 
 void* res_async ; 
 void* res_authenticate ; 
 void* res_authokay ; 
 int res_frags ; 
 scalar_t__ res_keyid ; 
 scalar_t__ res_offset ; 
 int res_opcode ; 
 scalar_t__ res_version ; 
 int /*<<< orphan*/ * rmt_addr ; 
 TYPE_3__ rpkt ; 
 int /*<<< orphan*/  stub1 (struct recvbuf*,int) ; 
 scalar_t__ sys_authenticate ; 
 int /*<<< orphan*/  sys_leap ; 

void
process_control(
	struct recvbuf *rbufp,
	int restrict_mask
	)
{
	struct ntp_control *pkt;
	int req_count;
	int req_data;
	const struct ctl_proc *cc;
	keyid_t *pkid;
	int properlen;
	size_t maclen;

	DPRINTF(3, ("in process_control()\n"));

	/*
	 * Save the addresses for error responses
	 */
	numctlreq++;
	rmt_addr = &rbufp->recv_srcadr;
	lcl_inter = rbufp->dstadr;
	pkt = (struct ntp_control *)&rbufp->recv_pkt;

	/*
	 * If the length is less than required for the header, or
	 * it is a response or a fragment, ignore this.
	 */
	if (rbufp->recv_length < (int)CTL_HEADER_LEN
	    || (CTL_RESPONSE | CTL_MORE | CTL_ERROR) & pkt->r_m_e_op
	    || pkt->offset != 0) {
		DPRINTF(1, ("invalid format in control packet\n"));
		if (rbufp->recv_length < (int)CTL_HEADER_LEN)
			numctltooshort++;
		if (CTL_RESPONSE & pkt->r_m_e_op)
			numctlinputresp++;
		if (CTL_MORE & pkt->r_m_e_op)
			numctlinputfrag++;
		if (CTL_ERROR & pkt->r_m_e_op)
			numctlinputerr++;
		if (pkt->offset != 0)
			numctlbadoffset++;
		return;
	}
	res_version = PKT_VERSION(pkt->li_vn_mode);
	if (res_version > NTP_VERSION || res_version < NTP_OLDVERSION) {
		DPRINTF(1, ("unknown version %d in control packet\n",
			    res_version));
		numctlbadversion++;
		return;
	}

	/*
	 * Pull enough data from the packet to make intelligent
	 * responses
	 */
	rpkt.li_vn_mode = PKT_LI_VN_MODE(sys_leap, res_version,
					 MODE_CONTROL);
	res_opcode = pkt->r_m_e_op;
	rpkt.sequence = pkt->sequence;
	rpkt.associd = pkt->associd;
	rpkt.status = 0;
	res_frags = 1;
	res_offset = 0;
	res_associd = htons(pkt->associd);
	res_async = FALSE;
	res_authenticate = FALSE;
	res_keyid = 0;
	res_authokay = FALSE;
	req_count = (int)ntohs(pkt->count);
	datanotbinflag = FALSE;
	datalinelen = 0;
	datasent = 0;
	datapt = rpkt.u.data;
	dataend = &rpkt.u.data[CTL_MAX_DATA_LEN];

	if ((rbufp->recv_length & 0x3) != 0)
		DPRINTF(3, ("Control packet length %d unrounded\n",
			    rbufp->recv_length));

	/*
	 * We're set up now. Make sure we've got at least enough
	 * incoming data space to match the count.
	 */
	req_data = rbufp->recv_length - CTL_HEADER_LEN;
	if (req_data < req_count || rbufp->recv_length & 0x3) {
		ctl_error(CERR_BADFMT);
		numctldatatooshort++;
		return;
	}

	properlen = req_count + CTL_HEADER_LEN;
	/* round up proper len to a 8 octet boundary */

	properlen = (properlen + 7) & ~7;
	maclen = rbufp->recv_length - properlen;
	if ((rbufp->recv_length & 3) == 0 &&
	    maclen >= MIN_MAC_LEN && maclen <= MAX_MAC_LEN &&
	    sys_authenticate) {
		res_authenticate = TRUE;
		pkid = (void *)((char *)pkt + properlen);
		res_keyid = ntohl(*pkid);
		DPRINTF(3, ("recv_len %d, properlen %d, wants auth with keyid %08x, MAC length=%zu\n",
			    rbufp->recv_length, properlen, res_keyid,
			    maclen));

		if (!authistrustedip(res_keyid, &rbufp->recv_srcadr))
			DPRINTF(3, ("invalid keyid %08x\n", res_keyid));
		else if (authdecrypt(res_keyid, (u_int32 *)pkt,
				     rbufp->recv_length - maclen,
				     maclen)) {
			res_authokay = TRUE;
			DPRINTF(3, ("authenticated okay\n"));
		} else {
			res_keyid = 0;
			DPRINTF(3, ("authentication failed\n"));
		}
	}

	/*
	 * Set up translate pointers
	 */
	reqpt = (char *)pkt->u.data;
	reqend = reqpt + req_count;

	/*
	 * Look for the opcode processor
	 */
	for (cc = control_codes; cc->control_code != NO_REQUEST; cc++) {
		if (cc->control_code == res_opcode) {
			DPRINTF(3, ("opcode %d, found command handler\n",
				    res_opcode));
			if (cc->flags == AUTH
			    && (!res_authokay
				|| res_keyid != ctl_auth_keyid)) {
				ctl_error(CERR_PERMISSION);
				return;
			}
			(cc->handler)(rbufp, restrict_mask);
			return;
		}
	}

	/*
	 * Can't find this one, return an error.
	 */
	numctlbadop++;
	ctl_error(CERR_BADOP);
	return;
}