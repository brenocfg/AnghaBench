#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct lladdr_info {int /*<<< orphan*/  addr; void* addr_string; } ;
struct TYPE_10__ {int /*<<< orphan*/  ndo_suppress_default_print; scalar_t__ ndo_eflag; scalar_t__ ndo_Hflag; int /*<<< orphan*/  ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_FRAME_IS_NULL (int /*<<< orphan*/ ) ; 
 scalar_t__ DATA_FRAME_IS_QOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTRACT_LE_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  FC_PROTECTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_SUBTYPE (int /*<<< orphan*/ ) ; 
 int FC_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE802_11_FC_LEN ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
#define  T_CTRL 130 
#define  T_DATA 129 
#define  T_MGMT 128 
 int /*<<< orphan*/  ctrl_body_print (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 void* etheraddr_string ; 
 scalar_t__ extract_header_length (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ extract_mesh_header_length (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_data_src_dst_mac (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mgmt_src_dst_mac (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_802_11_hdr_print (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 
 int llc_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__,scalar_t__,struct lladdr_info*,struct lladdr_info*) ; 
 int /*<<< orphan*/  mgmt_body_print (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ roundup2 (scalar_t__,int) ; 
 int /*<<< orphan*/  tstr ; 
 int /*<<< orphan*/  wep_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static u_int
ieee802_11_print(netdissect_options *ndo,
                 const u_char *p, u_int length, u_int orig_caplen, int pad,
                 u_int fcslen)
{
	uint16_t fc;
	u_int caplen, hdrlen, meshdrlen;
	struct lladdr_info src, dst;
	int llc_hdrlen;

	caplen = orig_caplen;
	/* Remove FCS, if present */
	if (length < fcslen) {
		ND_PRINT((ndo, "%s", tstr));
		return caplen;
	}
	length -= fcslen;
	if (caplen > length) {
		/* Amount of FCS in actual packet data, if any */
		fcslen = caplen - length;
		caplen -= fcslen;
		ndo->ndo_snapend -= fcslen;
	}

	if (caplen < IEEE802_11_FC_LEN) {
		ND_PRINT((ndo, "%s", tstr));
		return orig_caplen;
	}

	fc = EXTRACT_LE_16BITS(p);
	hdrlen = extract_header_length(ndo, fc);
	if (hdrlen == 0) {
		/* Unknown frame type or control frame subtype; quit. */
		return (0);
	}
	if (pad)
		hdrlen = roundup2(hdrlen, 4);
	if (ndo->ndo_Hflag && FC_TYPE(fc) == T_DATA &&
	    DATA_FRAME_IS_QOS(FC_SUBTYPE(fc))) {
		meshdrlen = extract_mesh_header_length(p+hdrlen);
		hdrlen += meshdrlen;
	} else
		meshdrlen = 0;

	if (caplen < hdrlen) {
		ND_PRINT((ndo, "%s", tstr));
		return hdrlen;
	}

	if (ndo->ndo_eflag)
		ieee_802_11_hdr_print(ndo, fc, p, hdrlen, meshdrlen);

	/*
	 * Go past the 802.11 header.
	 */
	length -= hdrlen;
	caplen -= hdrlen;
	p += hdrlen;

	src.addr_string = etheraddr_string;
	dst.addr_string = etheraddr_string;
	switch (FC_TYPE(fc)) {
	case T_MGMT:
		get_mgmt_src_dst_mac(p - hdrlen, &src.addr, &dst.addr);
		if (!mgmt_body_print(ndo, fc, src.addr, p, length)) {
			ND_PRINT((ndo, "%s", tstr));
			return hdrlen;
		}
		break;
	case T_CTRL:
		if (!ctrl_body_print(ndo, fc, p - hdrlen)) {
			ND_PRINT((ndo, "%s", tstr));
			return hdrlen;
		}
		break;
	case T_DATA:
		if (DATA_FRAME_IS_NULL(FC_SUBTYPE(fc)))
			return hdrlen;	/* no-data frame */
		/* There may be a problem w/ AP not having this bit set */
		if (FC_PROTECTED(fc)) {
			ND_PRINT((ndo, "Data"));
			if (!wep_print(ndo, p)) {
				ND_PRINT((ndo, "%s", tstr));
				return hdrlen;
			}
		} else {
			get_data_src_dst_mac(fc, p - hdrlen, &src.addr, &dst.addr);
			llc_hdrlen = llc_print(ndo, p, length, caplen, &src, &dst);
			if (llc_hdrlen < 0) {
				/*
				 * Some kinds of LLC packet we cannot
				 * handle intelligently
				 */
				if (!ndo->ndo_suppress_default_print)
					ND_DEFAULTPRINT(p, caplen);
				llc_hdrlen = -llc_hdrlen;
			}
			hdrlen += llc_hdrlen;
		}
		break;
	default:
		/* We shouldn't get here - we should already have quit */
		break;
	}

	return hdrlen;
}