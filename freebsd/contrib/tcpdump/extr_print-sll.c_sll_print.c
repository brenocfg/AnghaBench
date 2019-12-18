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
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_int ;
struct sll_header {int /*<<< orphan*/  sll_protocol; int /*<<< orphan*/  sll_addr; int /*<<< orphan*/  sll_halen; int /*<<< orphan*/  sll_pkttype; } ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_qflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int ETHERMTU ; 
 int EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
#define  LINUX_SLL_P_802_2 129 
#define  LINUX_SLL_P_802_3 128 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  etheraddr_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethertype_values ; 
 int /*<<< orphan*/  sll_pkttype_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline void
sll_print(netdissect_options *ndo, register const struct sll_header *sllp, u_int length)
{
	u_short ether_type;

        ND_PRINT((ndo, "%3s ",tok2str(sll_pkttype_values,"?",EXTRACT_16BITS(&sllp->sll_pkttype))));

	/*
	 * XXX - check the link-layer address type value?
	 * For now, we just assume 6 means Ethernet.
	 * XXX - print others as strings of hex?
	 */
	if (EXTRACT_16BITS(&sllp->sll_halen) == 6)
		ND_PRINT((ndo, "%s ", etheraddr_string(ndo, sllp->sll_addr)));

	if (!ndo->ndo_qflag) {
		ether_type = EXTRACT_16BITS(&sllp->sll_protocol);

		if (ether_type <= ETHERMTU) {
			/*
			 * Not an Ethernet type; what type is it?
			 */
			switch (ether_type) {

			case LINUX_SLL_P_802_3:
				/*
				 * Ethernet_802.3 IPX frame.
				 */
				ND_PRINT((ndo, "802.3"));
				break;

			case LINUX_SLL_P_802_2:
				/*
				 * 802.2.
				 */
				ND_PRINT((ndo, "802.2"));
				break;

			default:
				/*
				 * What is it?
				 */
				ND_PRINT((ndo, "ethertype Unknown (0x%04x)",
				    ether_type));
				break;
			}
		} else {
			ND_PRINT((ndo, "ethertype %s (0x%04x)",
			    tok2str(ethertype_values, "Unknown", ether_type),
			    ether_type));
		}
		ND_PRINT((ndo, ", length %u: ", length));
	}
}