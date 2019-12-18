#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct lladdr_info {void* addr_string; int /*<<< orphan*/  addr; } ;
struct ether_header {int /*<<< orphan*/  const ether_length_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  ndo_suppress_default_print; scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EDST (struct ether_header const*) ; 
 int /*<<< orphan*/  ESRC (struct ether_header const*) ; 
 scalar_t__ ETHERMTU ; 
 scalar_t__ ETHERTYPE_8021Q ; 
 scalar_t__ ETHERTYPE_8021Q9100 ; 
 scalar_t__ ETHERTYPE_8021Q9200 ; 
 scalar_t__ ETHERTYPE_8021QinQ ; 
 scalar_t__ ETHERTYPE_JUMBO ; 
 scalar_t__ ETHER_HDRLEN ; 
 void* EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ether_hdr_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 void* etheraddr_string ; 
 scalar_t__ ethertype_print (TYPE_1__*,scalar_t__,int /*<<< orphan*/  const*,scalar_t__,scalar_t__,struct lladdr_info*,struct lladdr_info*) ; 
 int /*<<< orphan*/  ethertype_values ; 
 int /*<<< orphan*/  ieee8021q_tci_string (void*) ; 
 int llc_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__,scalar_t__,struct lladdr_info*,struct lladdr_info*) ; 
 void stub1 (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 void stub2 (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 

u_int
ether_print(netdissect_options *ndo,
            const u_char *p, u_int length, u_int caplen,
            void (*print_encap_header)(netdissect_options *ndo, const u_char *), const u_char *encap_header_arg)
{
	const struct ether_header *ep;
	u_int orig_length;
	u_short length_type;
	u_int hdrlen;
	int llc_hdrlen;
	struct lladdr_info src, dst;

	if (caplen < ETHER_HDRLEN) {
		ND_PRINT((ndo, "[|ether]"));
		return (caplen);
	}
	if (length < ETHER_HDRLEN) {
		ND_PRINT((ndo, "[|ether]"));
		return (length);
	}

	if (ndo->ndo_eflag) {
		if (print_encap_header != NULL)
			(*print_encap_header)(ndo, encap_header_arg);
		ether_hdr_print(ndo, p, length);
	}
	orig_length = length;

	length -= ETHER_HDRLEN;
	caplen -= ETHER_HDRLEN;
	ep = (const struct ether_header *)p;
	p += ETHER_HDRLEN;
	hdrlen = ETHER_HDRLEN;

	src.addr = ESRC(ep);
	src.addr_string = etheraddr_string;
	dst.addr = EDST(ep);
	dst.addr_string = etheraddr_string;
	length_type = EXTRACT_16BITS(&ep->ether_length_type);

recurse:
	/*
	 * Is it (gag) an 802.3 encapsulation?
	 */
	if (length_type <= ETHERMTU) {
		/* Try to print the LLC-layer header & higher layers */
		llc_hdrlen = llc_print(ndo, p, length, caplen, &src, &dst);
		if (llc_hdrlen < 0) {
			/* packet type not known, print raw packet */
			if (!ndo->ndo_suppress_default_print)
				ND_DEFAULTPRINT(p, caplen);
			llc_hdrlen = -llc_hdrlen;
		}
		hdrlen += llc_hdrlen;
	} else if (length_type == ETHERTYPE_8021Q  ||
                length_type == ETHERTYPE_8021Q9100 ||
                length_type == ETHERTYPE_8021Q9200 ||
                length_type == ETHERTYPE_8021QinQ) {
		/*
		 * Print VLAN information, and then go back and process
		 * the enclosed type field.
		 */
		if (caplen < 4) {
			ND_PRINT((ndo, "[|vlan]"));
			return (hdrlen + caplen);
		}
		if (length < 4) {
			ND_PRINT((ndo, "[|vlan]"));
			return (hdrlen + length);
		}
	        if (ndo->ndo_eflag) {
			uint16_t tag = EXTRACT_16BITS(p);

			ND_PRINT((ndo, "%s, ", ieee8021q_tci_string(tag)));
		}

		length_type = EXTRACT_16BITS(p + 2);
		if (ndo->ndo_eflag && length_type > ETHERMTU)
			ND_PRINT((ndo, "ethertype %s, ", tok2str(ethertype_values,"0x%04x", length_type)));
		p += 4;
		length -= 4;
		caplen -= 4;
		hdrlen += 4;
		goto recurse;
	} else if (length_type == ETHERTYPE_JUMBO) {
		/*
		 * Alteon jumbo frames.
		 * See
		 *
		 *	http://tools.ietf.org/html/draft-ietf-isis-ext-eth-01
		 *
		 * which indicates that, following the type field,
		 * there's an LLC header and payload.
		 */
		/* Try to print the LLC-layer header & higher layers */
		llc_hdrlen = llc_print(ndo, p, length, caplen, &src, &dst);
		if (llc_hdrlen < 0) {
			/* packet type not known, print raw packet */
			if (!ndo->ndo_suppress_default_print)
				ND_DEFAULTPRINT(p, caplen);
			llc_hdrlen = -llc_hdrlen;
		}
		hdrlen += llc_hdrlen;
	} else {
		if (ethertype_print(ndo, length_type, p, length, caplen, &src, &dst) == 0) {
			/* type not known, print raw packet */
			if (!ndo->ndo_eflag) {
				if (print_encap_header != NULL)
					(*print_encap_header)(ndo, encap_header_arg);
				ether_hdr_print(ndo, (const u_char *)ep, orig_length);
			}

			if (!ndo->ndo_suppress_default_print)
				ND_DEFAULTPRINT(p, caplen);
		}
	}
	return (hdrlen);
}