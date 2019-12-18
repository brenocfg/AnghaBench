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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ether_header {int /*<<< orphan*/  ether_length_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_qflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EDST (struct ether_header const*) ; 
 int /*<<< orphan*/  ESRC (struct ether_header const*) ; 
 scalar_t__ ETHERMTU ; 
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  etheraddr_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethertype_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static inline void
ether_hdr_print(netdissect_options *ndo,
                const u_char *bp, u_int length)
{
	register const struct ether_header *ep;
	uint16_t length_type;

	ep = (const struct ether_header *)bp;

	ND_PRINT((ndo, "%s > %s",
		     etheraddr_string(ndo, ESRC(ep)),
		     etheraddr_string(ndo, EDST(ep))));

	length_type = EXTRACT_16BITS(&ep->ether_length_type);
	if (!ndo->ndo_qflag) {
	        if (length_type <= ETHERMTU) {
		        ND_PRINT((ndo, ", 802.3"));
			length = length_type;
		} else
		        ND_PRINT((ndo, ", ethertype %s (0x%04x)",
				       tok2str(ethertype_values,"Unknown", length_type),
                                       length_type));
        } else {
                if (length_type <= ETHERMTU) {
                        ND_PRINT((ndo, ", 802.3"));
			length = length_type;
		} else
                        ND_PRINT((ndo, ", %s", tok2str(ethertype_values,"Unknown Ethertype (0x%04x)", length_type)));
        }

	ND_PRINT((ndo, ", length %u: ", length));
}