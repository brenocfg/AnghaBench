#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int u_int ;
typedef  scalar_t__ u_char ;
struct lladdr_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  (* addr_string ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_LE_16BITS (scalar_t__ const*) ; 
 int LLCSAP_8021D ; 
 int LLCSAP_GLOBAL ; 
 int LLCSAP_IP ; 
 int LLCSAP_IPX ; 
 int LLCSAP_ISONS ; 
 int LLCSAP_NETBEUI ; 
 int LLCSAP_SNAP ; 
 int LLC_GSAP ; 
 int LLC_IG ; 
 int /*<<< orphan*/  LLC_IS_NR (int) ; 
 int LLC_IS_POLL ; 
 int /*<<< orphan*/  LLC_I_NS (int) ; 
 int LLC_S_CMD (int) ; 
 int LLC_S_FMT ; 
 int LLC_UI ; 
 int LLC_U_CMD (int) ; 
 int LLC_U_FMT ; 
 int LLC_U_POLL ; 
 int LLC_XID ; 
 scalar_t__ const LLC_XID_FI ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (scalar_t__ const*,int) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_print (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  ipx_print (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  isoclns_print (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  llc_cmd_values ; 
 int /*<<< orphan*/  llc_flag_values ; 
 int /*<<< orphan*/  llc_ig_flag_values ; 
 int /*<<< orphan*/  llc_supervisory_values ; 
 int /*<<< orphan*/  llc_values ; 
 int /*<<< orphan*/  netbeui_print (TYPE_1__*,int,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  snap_print (TYPE_1__*,scalar_t__ const*,int,int,struct lladdr_info const*,struct lladdr_info const*,int) ; 
 int /*<<< orphan*/  stp_print (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

int
llc_print(netdissect_options *ndo, const u_char *p, u_int length, u_int caplen,
	  const struct lladdr_info *src, const struct lladdr_info *dst)
{
	uint8_t dsap_field, dsap, ssap_field, ssap;
	uint16_t control;
	int hdrlen;
	int is_u;

	if (caplen < 3) {
		ND_PRINT((ndo, "[|llc]"));
		ND_DEFAULTPRINT((const u_char *)p, caplen);
		return (caplen);
	}
	if (length < 3) {
		ND_PRINT((ndo, "[|llc]"));
		ND_DEFAULTPRINT((const u_char *)p, caplen);
		return (length);
	}

	dsap_field = *p;
	ssap_field = *(p + 1);

	/*
	 * OK, what type of LLC frame is this?  The length
	 * of the control field depends on that - I frames
	 * have a two-byte control field, and U frames have
	 * a one-byte control field.
	 */
	control = *(p + 2);
	if ((control & LLC_U_FMT) == LLC_U_FMT) {
		/*
		 * U frame.
		 */
		is_u = 1;
		hdrlen = 3;	/* DSAP, SSAP, 1-byte control field */
	} else {
		/*
		 * The control field in I and S frames is
		 * 2 bytes...
		 */
		if (caplen < 4) {
			ND_PRINT((ndo, "[|llc]"));
			ND_DEFAULTPRINT((const u_char *)p, caplen);
			return (caplen);
		}
		if (length < 4) {
			ND_PRINT((ndo, "[|llc]"));
			ND_DEFAULTPRINT((const u_char *)p, caplen);
			return (length);
		}

		/*
		 * ...and is little-endian.
		 */
		control = EXTRACT_LE_16BITS(p + 2);
		is_u = 0;
		hdrlen = 4;	/* DSAP, SSAP, 2-byte control field */
	}

	if (ssap_field == LLCSAP_GLOBAL && dsap_field == LLCSAP_GLOBAL) {
		/*
		 * This is an Ethernet_802.3 IPX frame; it has an
		 * 802.3 header (i.e., an Ethernet header where the
		 * type/length field is <= ETHERMTU, i.e. it's a length
		 * field, not a type field), but has no 802.2 header -
		 * the IPX packet starts right after the Ethernet header,
		 * with a signature of two bytes of 0xFF (which is
		 * LLCSAP_GLOBAL).
		 *
		 * (It might also have been an Ethernet_802.3 IPX at
		 * one time, but got bridged onto another network,
		 * such as an 802.11 network; this has appeared in at
		 * least one capture file.)
		 */

            if (ndo->ndo_eflag)
		ND_PRINT((ndo, "IPX 802.3: "));

            ipx_print(ndo, p, length);
            return (0);		/* no LLC header */
	}

	dsap = dsap_field & ~LLC_IG;
	ssap = ssap_field & ~LLC_GSAP;

	if (ndo->ndo_eflag) {
                ND_PRINT((ndo, "LLC, dsap %s (0x%02x) %s, ssap %s (0x%02x) %s",
                       tok2str(llc_values, "Unknown", dsap),
                       dsap,
                       tok2str(llc_ig_flag_values, "Unknown", dsap_field & LLC_IG),
                       tok2str(llc_values, "Unknown", ssap),
                       ssap,
                       tok2str(llc_flag_values, "Unknown", ssap_field & LLC_GSAP)));

		if (is_u) {
			ND_PRINT((ndo, ", ctrl 0x%02x: ", control));
		} else {
			ND_PRINT((ndo, ", ctrl 0x%04x: ", control));
		}
	}

	/*
	 * Skip LLC header.
	 */
	p += hdrlen;
	length -= hdrlen;
	caplen -= hdrlen;

	if (ssap == LLCSAP_SNAP && dsap == LLCSAP_SNAP
	    && control == LLC_UI) {
		/*
		 * XXX - what *is* the right bridge pad value here?
		 * Does anybody ever bridge one form of LAN traffic
		 * over a networking type that uses 802.2 LLC?
		 */
		if (!snap_print(ndo, p, length, caplen, src, dst, 2)) {
			/*
			 * Unknown packet type; tell our caller, by
			 * returning a negative value, so they
			 * can print the raw packet.
			 */
			return (-(hdrlen + 5));	/* include LLC and SNAP header */
		} else
			return (hdrlen + 5);	/* include LLC and SNAP header */
	}

	if (ssap == LLCSAP_8021D && dsap == LLCSAP_8021D &&
	    control == LLC_UI) {
		stp_print(ndo, p, length);
		return (hdrlen);
	}

	if (ssap == LLCSAP_IP && dsap == LLCSAP_IP &&
	    control == LLC_UI) {
		/*
		 * This is an RFC 948-style IP packet, with
		 * an 802.3 header and an 802.2 LLC header
		 * with the source and destination SAPs being
		 * the IP SAP.
		 */
		ip_print(ndo, p, length);
		return (hdrlen);
	}

	if (ssap == LLCSAP_IPX && dsap == LLCSAP_IPX &&
	    control == LLC_UI) {
		/*
		 * This is an Ethernet_802.2 IPX frame, with an 802.3
		 * header and an 802.2 LLC header with the source and
		 * destination SAPs being the IPX SAP.
		 */
                if (ndo->ndo_eflag)
                        ND_PRINT((ndo, "IPX 802.2: "));

		ipx_print(ndo, p, length);
		return (hdrlen);
	}

#ifdef ENABLE_SMB
	if (ssap == LLCSAP_NETBEUI && dsap == LLCSAP_NETBEUI
	    && (!(control & LLC_S_FMT) || control == LLC_U_FMT)) {
		/*
		 * we don't actually have a full netbeui parser yet, but the
		 * smb parser can handle many smb-in-netbeui packets, which
		 * is very useful, so we call that
		 *
		 * We don't call it for S frames, however, just I frames
		 * (which are frames that don't have the low-order bit,
		 * LLC_S_FMT, set in the first byte of the control field)
		 * and UI frames (whose control field is just 3, LLC_U_FMT).
		 */
		netbeui_print(ndo, control, p, length);
		return (hdrlen);
	}
#endif
	if (ssap == LLCSAP_ISONS && dsap == LLCSAP_ISONS
	    && control == LLC_UI) {
		isoclns_print(ndo, p, length);
		return (hdrlen);
	}

	if (!ndo->ndo_eflag) {
		if (ssap == dsap) {
			if (src == NULL || dst == NULL)
				ND_PRINT((ndo, "%s ", tok2str(llc_values, "Unknown DSAP 0x%02x", dsap)));
			else
				ND_PRINT((ndo, "%s > %s %s ",
						(src->addr_string)(ndo, src->addr),
						(dst->addr_string)(ndo, dst->addr),
						tok2str(llc_values, "Unknown DSAP 0x%02x", dsap)));
		} else {
			if (src == NULL || dst == NULL)
				ND_PRINT((ndo, "%s > %s ",
                                        tok2str(llc_values, "Unknown SSAP 0x%02x", ssap),
					tok2str(llc_values, "Unknown DSAP 0x%02x", dsap)));
			else
				ND_PRINT((ndo, "%s %s > %s %s ",
					(src->addr_string)(ndo, src->addr),
                                        tok2str(llc_values, "Unknown SSAP 0x%02x", ssap),
					(dst->addr_string)(ndo, dst->addr),
					tok2str(llc_values, "Unknown DSAP 0x%02x", dsap)));
		}
	}

	if (is_u) {
		ND_PRINT((ndo, "Unnumbered, %s, Flags [%s], length %u",
                       tok2str(llc_cmd_values, "%02x", LLC_U_CMD(control)),
                       tok2str(llc_flag_values,"?",(ssap_field & LLC_GSAP) | (control & LLC_U_POLL)),
                       length + hdrlen));

		if ((control & ~LLC_U_POLL) == LLC_XID) {
			if (length == 0) {
				/*
				 * XID with no payload.
				 * This could, for example, be an SNA
				 * "short form" XID.
                                 */
				return (hdrlen);
			}
			if (caplen < 1) {
				ND_PRINT((ndo, "[|llc]"));
				if (caplen > 0)
					ND_DEFAULTPRINT((const u_char *)p, caplen);
				return (hdrlen);
			}
			if (*p == LLC_XID_FI) {
				if (caplen < 3 || length < 3) {
					ND_PRINT((ndo, "[|llc]"));
					if (caplen > 0)
						ND_DEFAULTPRINT((const u_char *)p, caplen);
				} else
					ND_PRINT((ndo, ": %02x %02x", p[1], p[2]));
				return (hdrlen);
			}
		}
	} else {
		if ((control & LLC_S_FMT) == LLC_S_FMT) {
			ND_PRINT((ndo, "Supervisory, %s, rcv seq %u, Flags [%s], length %u",
				tok2str(llc_supervisory_values,"?",LLC_S_CMD(control)),
				LLC_IS_NR(control),
				tok2str(llc_flag_values,"?",(ssap_field & LLC_GSAP) | (control & LLC_IS_POLL)),
                                length + hdrlen));
			return (hdrlen);	/* no payload to print */
		} else {
			ND_PRINT((ndo, "Information, send seq %u, rcv seq %u, Flags [%s], length %u",
				LLC_I_NS(control),
				LLC_IS_NR(control),
				tok2str(llc_flag_values,"?",(ssap_field & LLC_GSAP) | (control & LLC_IS_POLL)),
                                length + hdrlen));
		}
	}
	return (-hdrlen);
}