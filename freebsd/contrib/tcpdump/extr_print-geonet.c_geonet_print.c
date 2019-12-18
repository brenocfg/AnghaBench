#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
typedef  int u_char ;
struct lladdr_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  (* addr_string ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int const*,int) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  print_btp (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  print_btp_body (TYPE_1__*,int const*) ; 
 int print_long_pos_vector (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
geonet_print(netdissect_options *ndo, const u_char *bp, u_int length,
	     const struct lladdr_info *src)
{
	int version;
	int next_hdr;
	int hdr_type;
	int hdr_subtype;
	uint16_t payload_length;
	int hop_limit;
	const char *next_hdr_txt = "Unknown";
	const char *hdr_type_txt = "Unknown";
	int hdr_size = -1;

	ND_PRINT((ndo, "GeoNet "));
	if (src != NULL)
		ND_PRINT((ndo, "src:%s", (src->addr_string)(ndo, src->addr)));
	ND_PRINT((ndo, "; "));

	/* Process Common Header */
	if (length < 36)
		goto invalid;

	ND_TCHECK2(*bp, 8);
	version = bp[0] >> 4;
	next_hdr = bp[0] & 0x0f;
	hdr_type = bp[1] >> 4;
	hdr_subtype = bp[1] & 0x0f;
	payload_length = EXTRACT_16BITS(bp+4);
	hop_limit = bp[7];

	switch (next_hdr) {
		case 0: next_hdr_txt = "Any"; break;
		case 1: next_hdr_txt = "BTP-A"; break;
		case 2: next_hdr_txt = "BTP-B"; break;
		case 3: next_hdr_txt = "IPv6"; break;
	}

	switch (hdr_type) {
		case 0: hdr_type_txt = "Any"; break;
		case 1: hdr_type_txt = "Beacon"; break;
		case 2: hdr_type_txt = "GeoUnicast"; break;
		case 3: switch (hdr_subtype) {
				case 0: hdr_type_txt = "GeoAnycastCircle"; break;
				case 1: hdr_type_txt = "GeoAnycastRect"; break;
				case 2: hdr_type_txt = "GeoAnycastElipse"; break;
			}
			break;
		case 4: switch (hdr_subtype) {
				case 0: hdr_type_txt = "GeoBroadcastCircle"; break;
				case 1: hdr_type_txt = "GeoBroadcastRect"; break;
				case 2: hdr_type_txt = "GeoBroadcastElipse"; break;
			}
			break;
		case 5: switch (hdr_subtype) {
				case 0: hdr_type_txt = "TopoScopeBcast-SH"; break;
				case 1: hdr_type_txt = "TopoScopeBcast-MH"; break;
			}
			break;
		case 6: switch (hdr_subtype) {
				case 0: hdr_type_txt = "LocService-Request"; break;
				case 1: hdr_type_txt = "LocService-Reply"; break;
			}
			break;
	}

	ND_PRINT((ndo, "v:%d ", version));
	ND_PRINT((ndo, "NH:%d-%s ", next_hdr, next_hdr_txt));
	ND_PRINT((ndo, "HT:%d-%d-%s ", hdr_type, hdr_subtype, hdr_type_txt));
	ND_PRINT((ndo, "HopLim:%d ", hop_limit));
	ND_PRINT((ndo, "Payload:%d ", payload_length));
	if (print_long_pos_vector(ndo, bp + 8) == -1)
		goto trunc;

	/* Skip Common Header */
	length -= 36;
	bp += 36;

	/* Process Extended Headers */
	switch (hdr_type) {
		case 0: /* Any */
			hdr_size = 0;
			break;
		case 1: /* Beacon */
			hdr_size = 0;
			break;
		case 2: /* GeoUnicast */
			break;
		case 3: switch (hdr_subtype) {
				case 0: /* GeoAnycastCircle */
					break;
				case 1: /* GeoAnycastRect */
					break;
				case 2: /* GeoAnycastElipse */
					break;
			}
			break;
		case 4: switch (hdr_subtype) {
				case 0: /* GeoBroadcastCircle */
					break;
				case 1: /* GeoBroadcastRect */
					break;
				case 2: /* GeoBroadcastElipse */
					break;
			}
			break;
		case 5: switch (hdr_subtype) {
				case 0: /* TopoScopeBcast-SH */
					hdr_size = 0;
					break;
				case 1: /* TopoScopeBcast-MH */
					hdr_size = 68 - 36;
					break;
			}
			break;
		case 6: switch (hdr_subtype) {
				case 0: /* LocService-Request */
					break;
				case 1: /* LocService-Reply */
					break;
			}
			break;
	}

	/* Skip Extended headers */
	if (hdr_size >= 0) {
		if (length < (u_int)hdr_size)
			goto invalid;
		ND_TCHECK2(*bp, hdr_size);
		length -= hdr_size;
		bp += hdr_size;
		switch (next_hdr) {
			case 0: /* Any */
				break;
			case 1:
			case 2: /* BTP A/B */
				if (length < 4)
					goto invalid;
				ND_TCHECK2(*bp, 4);
				print_btp(ndo, bp);
				length -= 4;
				bp += 4;
				if (length >= 2) {
					/*
					 * XXX - did print_btp_body()
					 * return if length < 2
					 * because this is optional,
					 * or was that just not
					 * reporting genuine errors?
					 */
					ND_TCHECK2(*bp, 2);
					print_btp_body(ndo, bp);
				}
				break;
			case 3: /* IPv6 */
				break;
		}
	}

	/* Print user data part */
	if (ndo->ndo_vflag)
		ND_DEFAULTPRINT(bp, length);
	return;

invalid:
	ND_PRINT((ndo, " Malformed (small) "));
	/* XXX - print the remaining data as hex? */
	return;

trunc:
	ND_PRINT((ndo, "[|geonet]"));
}