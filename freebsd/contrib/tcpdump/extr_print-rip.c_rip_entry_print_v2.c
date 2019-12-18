#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int u_short ;
typedef  scalar_t__ u_int ;
typedef  char u_char ;
struct rip_netinfo {int /*<<< orphan*/  rip_router; int /*<<< orphan*/  rip_metric; int /*<<< orphan*/  const rip_tag; int /*<<< orphan*/  rip_dest_mask; int /*<<< orphan*/  rip_dest; int /*<<< orphan*/  const rip_family; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int BSD_AFNUM_INET ; 
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 scalar_t__ ND_ISPRINT (char const) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 scalar_t__ RIP_AUTHLEN ; 
 unsigned int const RIP_ROUTELEN ; 
 int /*<<< orphan*/  bsd_af_values ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mask2plen (scalar_t__) ; 
 int /*<<< orphan*/  print_unknown_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,unsigned int const) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static unsigned
rip_entry_print_v2(netdissect_options *ndo,
                   register const struct rip_netinfo *ni, const unsigned remaining)
{
	register u_short family;

	family = EXTRACT_16BITS(&ni->rip_family);
	if (family == 0xFFFF) { /* variable-sized authentication structures */
		uint16_t auth_type = EXTRACT_16BITS(&ni->rip_tag);
		if (auth_type == 2) {
			register const u_char *p = (const u_char *)&ni->rip_dest;
			u_int i = 0;
			ND_PRINT((ndo, "\n\t  Simple Text Authentication data: "));
			for (; i < RIP_AUTHLEN; p++, i++)
				ND_PRINT((ndo, "%c", ND_ISPRINT(*p) ? *p : '.'));
		} else if (auth_type == 3) {
			ND_PRINT((ndo, "\n\t  Auth header:"));
			ND_PRINT((ndo, " Packet Len %u,", EXTRACT_16BITS((const uint8_t *)ni + 4)));
			ND_PRINT((ndo, " Key-ID %u,", *((const uint8_t *)ni + 6)));
			ND_PRINT((ndo, " Auth Data Len %u,", *((const uint8_t *)ni + 7)));
			ND_PRINT((ndo, " SeqNo %u,", EXTRACT_32BITS(&ni->rip_dest_mask)));
			ND_PRINT((ndo, " MBZ %u,", EXTRACT_32BITS(&ni->rip_router)));
			ND_PRINT((ndo, " MBZ %u", EXTRACT_32BITS(&ni->rip_metric)));
		} else if (auth_type == 1) {
			ND_PRINT((ndo, "\n\t  Auth trailer:"));
			print_unknown_data(ndo, (const uint8_t *)&ni->rip_dest, "\n\t  ", remaining);
			return remaining; /* AT spans till the packet end */
		} else {
			ND_PRINT((ndo, "\n\t  Unknown (%u) Authentication data:",
			       EXTRACT_16BITS(&ni->rip_tag)));
			print_unknown_data(ndo, (const uint8_t *)&ni->rip_dest, "\n\t  ", remaining);
		}
	} else if (family != BSD_AFNUM_INET && family != 0) {
		ND_PRINT((ndo, "\n\t  AFI %s", tok2str(bsd_af_values, "Unknown (%u)", family)));
                print_unknown_data(ndo, (const uint8_t *)&ni->rip_tag, "\n\t  ", RIP_ROUTELEN-2);
	} else { /* BSD_AFNUM_INET or AFI 0 */
		ND_PRINT((ndo, "\n\t  AFI %s, %15s/%-2d, tag 0x%04x, metric: %u, next-hop: ",
                       tok2str(bsd_af_values, "%u", family),
                       ipaddr_string(ndo, &ni->rip_dest),
		       mask2plen(EXTRACT_32BITS(&ni->rip_dest_mask)),
                       EXTRACT_16BITS(&ni->rip_tag),
                       EXTRACT_32BITS(&ni->rip_metric)));
		if (EXTRACT_32BITS(&ni->rip_router))
			ND_PRINT((ndo, "%s", ipaddr_string(ndo, &ni->rip_router)));
		else
			ND_PRINT((ndo, "self"));
	}
	return sizeof (*ni);
}