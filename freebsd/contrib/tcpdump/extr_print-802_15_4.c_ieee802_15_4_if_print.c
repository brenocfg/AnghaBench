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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int caplen; } ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_suppress_default_print; scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_LE_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXTRACT_LE_8BITS (int /*<<< orphan*/  const*) ; 
#define  FC_ADDRESSING_MODE_LONG 131 
#define  FC_ADDRESSING_MODE_NONE 130 
#define  FC_ADDRESSING_MODE_RESERVED 129 
#define  FC_ADDRESSING_MODE_SHORT 128 
 int FC_DEST_ADDRESSING_MODE (int) ; 
 size_t FC_FRAME_TYPE (int) ; 
 int FC_PAN_ID_COMPRESSION ; 
 int FC_SRC_ADDRESSING_MODE (int) ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/ * ftypes ; 
 int /*<<< orphan*/  le64addr_string (TYPE_1__*,int /*<<< orphan*/  const*) ; 

u_int
ieee802_15_4_if_print(netdissect_options *ndo,
                      const struct pcap_pkthdr *h, const u_char *p)
{
	u_int caplen = h->caplen;
	u_int hdrlen;
	uint16_t fc;
	uint8_t seq;
	uint16_t panid = 0;

	if (caplen < 3) {
		ND_PRINT((ndo, "[|802.15.4]"));
		return caplen;
	}
	hdrlen = 3;

	fc = EXTRACT_LE_16BITS(p);
	seq = EXTRACT_LE_8BITS(p + 2);

	p += 3;
	caplen -= 3;

	ND_PRINT((ndo,"IEEE 802.15.4 %s packet ", ftypes[FC_FRAME_TYPE(fc)]));
	if (ndo->ndo_vflag)
		ND_PRINT((ndo,"seq %02x ", seq));

	/*
	 * Destination address and PAN ID, if present.
	 */
	switch (FC_DEST_ADDRESSING_MODE(fc)) {
	case FC_ADDRESSING_MODE_NONE:
		if (fc & FC_PAN_ID_COMPRESSION) {
			/*
			 * PAN ID compression; this requires that both
			 * the source and destination addresses be present,
			 * but the destination address is missing.
			 */
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"none "));
		break;
	case FC_ADDRESSING_MODE_RESERVED:
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"reserved destination addressing mode"));
		return hdrlen;
	case FC_ADDRESSING_MODE_SHORT:
		if (caplen < 2) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		panid = EXTRACT_LE_16BITS(p);
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		if (caplen < 2) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"%04x:%04x ", panid, EXTRACT_LE_16BITS(p)));
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		break;
	case FC_ADDRESSING_MODE_LONG:
		if (caplen < 2) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		panid = EXTRACT_LE_16BITS(p);
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		if (caplen < 8) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"%04x:%s ", panid, le64addr_string(ndo, p)));
		p += 8;
		caplen -= 8;
		hdrlen += 8;
		break;
	}
	if (ndo->ndo_vflag)
		ND_PRINT((ndo,"< "));

	/*
	 * Source address and PAN ID, if present.
	 */
	switch (FC_SRC_ADDRESSING_MODE(fc)) {
	case FC_ADDRESSING_MODE_NONE:
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"none "));
		break;
	case FC_ADDRESSING_MODE_RESERVED:
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"reserved source addressing mode"));
		return 0;
	case FC_ADDRESSING_MODE_SHORT:
		if (!(fc & FC_PAN_ID_COMPRESSION)) {
			/*
			 * The source PAN ID is not compressed out, so
			 * fetch it.  (Otherwise, we'll use the destination
			 * PAN ID, fetched above.)
			 */
			if (caplen < 2) {
				ND_PRINT((ndo, "[|802.15.4]"));
				return hdrlen;
			}
			panid = EXTRACT_LE_16BITS(p);
			p += 2;
			caplen -= 2;
			hdrlen += 2;
		}
		if (caplen < 2) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"%04x:%04x ", panid, EXTRACT_LE_16BITS(p)));
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		break;
	case FC_ADDRESSING_MODE_LONG:
		if (!(fc & FC_PAN_ID_COMPRESSION)) {
			/*
			 * The source PAN ID is not compressed out, so
			 * fetch it.  (Otherwise, we'll use the destination
			 * PAN ID, fetched above.)
			 */
			if (caplen < 2) {
				ND_PRINT((ndo, "[|802.15.4]"));
				return hdrlen;
			}
			panid = EXTRACT_LE_16BITS(p);
			p += 2;
			caplen -= 2;
			hdrlen += 2;
		}
		if (caplen < 8) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"%04x:%s ", panid, le64addr_string(ndo, p)));
		p += 8;
		caplen -= 8;
		hdrlen += 8;
		break;
	}

	if (!ndo->ndo_suppress_default_print)
		ND_DEFAULTPRINT(p, caplen);

	return hdrlen;
}